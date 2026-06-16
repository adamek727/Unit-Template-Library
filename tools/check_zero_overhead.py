#!/usr/bin/env python3
# Copyright (C) 2024 Adam Ligocki
# Distributed under MIT licence
#
# Zero-overhead proof. Compiles tests/asm/zero_overhead.cpp to assembly at -O2
# and asserts that every `unit_*` function emits the same machine code as its
# `raw_*` twin. If the unit wrapper ever stops being free (an accidental copy,
# a lost inline, a stray conversion), the matching pair diverges and this exits
# non-zero -- turning the zero-overhead claim into a regression test.
#
# Usage: tools/check_zero_overhead.py [compiler]   (default: c++)

import os
import re
import subprocess
import sys
import tempfile

# raw_<name> must compile to the same body as unit_<name> for each name here.
PAIRS = ["add", "sub", "scale", "negate", "mul", "div", "fma", "inv"]

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SOURCE = os.path.join(REPO_ROOT, "tests", "asm", "zero_overhead.cpp")
INCLUDE = os.path.join(REPO_ROOT, "include")

# Directives and labels that carry no semantics for a branchless leaf function.
_DROP_PREFIXES = (
    ".cfi", ".size", ".type", ".globl", ".global", ".local", ".weak",
    ".align", ".p2align", ".section", ".text", ".data", ".ident", ".file",
    ".set", ".loc", ".seh", ".def", ".scl", ".endef", ".addrsig",
)

# Data directives that make up a constant-pool entry's value.
_DATA_DIRECTIVES = (
    ".long", ".quad", ".byte", ".word", ".short", ".value", ".octa",
    ".zero", ".single", ".double", ".ascii", ".asciz",
)

# Constant-pool labels: gcc emits .LC0, clang emits .LCPI<n>_<m>. Distinct
# functions get distinct slot names for the *same* constant, so references are
# compared by resolved value, not by slot name.
_CONST_LABEL = re.compile(r"\.LC[A-Za-z0-9_]+")


def compile_to_asm(compiler):
    out = os.path.join(tempfile.mkdtemp(), "zero_overhead.s")
    cmd = [
        compiler, "-std=c++17", "-O2", "-DNDEBUG",
        "-fno-asynchronous-unwind-tables",
        "-S", "-I", INCLUDE, "-o", out, SOURCE,
    ]
    subprocess.run(cmd, check=True)
    with open(out) as f:
        return f.read()


def _code(line):
    """Line with any trailing comment and surrounding whitespace removed.

    clang annotates labels with a trailing comment (`raw_add: # @raw_add`),
    so matching must ignore everything after `#`. (x86 AT&T uses `#` only for
    comments; immediates use `$`.)
    """
    return line.split("#", 1)[0].strip()


def collect_constants(asm):
    """Map each constant-pool label to the normalized bytes it defines."""
    consts = {}
    lines = asm.splitlines()
    i = 0
    while i < len(lines):
        code = _code(lines[i])
        m = re.match(r"^(\.LC[A-Za-z0-9_]+):$", code)
        if not m:
            i += 1
            continue
        data = []
        j = i + 1
        while j < len(lines):
            c = _code(lines[j])
            if c == "":
                j += 1
                continue
            if c.startswith(_DATA_DIRECTIVES):
                data.append(re.sub(r"\s+", " ", c))
                j += 1
                continue
            break
        consts[m.group(1)] = " ".join(data)
        i = j
    return consts


def extract_body(asm, name, consts):
    """Return the normalized instruction list of function `name`."""
    lines = asm.splitlines()
    start = None
    label = name + ":"
    for i, line in enumerate(lines):
        if _code(line) == label:
            start = i + 1
            break
    if start is None:
        raise SystemExit(f"symbol '{name}' not found in assembly")

    body = []
    for line in lines[start:]:
        code = _code(line)
        # End of this function: a new top-level label or the .size marker.
        if re.match(r"^[A-Za-z_][A-Za-z0-9_]*:$", code):
            break
        if code.startswith(".size"):
            break
        body.append(line)

    return normalize(body, consts)


def _resolve_consts(text, consts):
    """Replace constant-pool label references with the value they point at, so
    the same constant in differently-named slots compares equal."""
    return _CONST_LABEL.sub(
        lambda m: "const(%s)" % consts.get(m.group(0), m.group(0)), text)


def normalize(body, consts):
    out = []
    for line in body:
        line = line.split("#", 1)[0]          # strip comments
        stripped = line.strip()
        if not stripped:
            continue
        if stripped.startswith(_DROP_PREFIXES):
            continue
        if re.match(r"^\.L[A-Za-z0-9_$.]*:$", stripped):  # local label def
            continue
        collapsed = re.sub(r"\s+", " ", stripped)         # collapse whitespace
        out.append(_resolve_consts(collapsed, consts))
    return out


def main():
    compiler = sys.argv[1] if len(sys.argv) > 1 else "c++"
    print(f"zero-overhead proof: {compiler} -O2")
    try:
        asm = compile_to_asm(compiler)
    except subprocess.CalledProcessError as exc:
        raise SystemExit(f"compilation failed: {exc}")

    consts = collect_constants(asm)
    failures = 0
    for name in PAIRS:
        raw = extract_body(asm, "raw_" + name, consts)
        unit = extract_body(asm, "unit_" + name, consts)
        if raw == unit:
            print(f"  ok    {name:<8} ({len(raw)} insns identical)")
        else:
            failures += 1
            print(f"  FAIL  {name:<8} raw vs unit assembly differ:")
            print("    raw_%s : %s" % (name, " | ".join(raw)))
            print("    unit_%s: %s" % (name, " | ".join(unit)))

    if failures:
        raise SystemExit(f"\n{failures} pair(s) showed overhead; zero-overhead proof failed")
    print(f"\nall {len(PAIRS)} pairs identical: unit arithmetic is zero-overhead")


if __name__ == "__main__":
    main()
