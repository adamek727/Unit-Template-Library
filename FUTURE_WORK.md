# Future Work

Roadmap after v2.0.0. Priorities below are informed by a June 2026 survey of the
leading C++ and Rust units libraries (see **References**); each item notes how
the field handles it, so we adopt what works and skip what doesn't.

## Positioning — the lane to own

We cannot out-feature **mp-units** (C++20, ISQ quantity-kinds, affine quantities,
the reference implementation for a future `std::quantity`) nor out-adopt
**nholthaus/units** or Rust's **uom**. Competing on scope is a losing game.

The winnable lane is the one mp-units cedes and that no C++ library holds
cleanly: the **friction-free, fast-compiling, embedded-friendly, header-only
C++17 library with best-in-class error messages, a CI-proven zero-overhead
guarantee, and an explicit upgrade path to `std::quantity`.** Our `int8_t`
exponent design already implies fast compiles and more readable errors than the
`typenum`/`std::ratio`-tuple libraries; we should lean into that rather than
chase ISQ completeness. Target audience: everyone not yet on C++20, and
MISRA/embedded shops that forbid heavy dependencies.

## Completed (v2.1) — PRs #12–#15 (in review)

1. **Badges and release automation** — CI/docs/release badges; a tag-triggered
   GitHub Release drawing notes from `CHANGELOG.md`.
2. **clang-format and a CI format check** — house style locked before external
   contributions arrive.
3. **Zero-overhead proof in CI** — `tools/check_zero_overhead.py` asserts unit
   arithmetic and raw arithmetic emit byte-identical assembly (gcc + clang).
   Few competitors have this as an in-tree regression test — it is a genuine
   differentiator, not just a claim.
4. **Property-based tests** — randomized algebraic identities guarding the
   mapper and operators.

## Phase A — discoverability and trust (cheap, highest ROI)

5. **Packaging** — vcpkg + Conan submissions and a CMake
   `FetchContent`/`find_package` story. We have zero package-manager presence;
   frictionless install is empirically the single biggest adoption lever (it is
   why nholthaus won despite its flaws, and why Au ships a single-header
   *generator*). Pure upside. (Was item #7.)
6. **`std::format` support** — we expose `operator<<` only; mp-units and Au both
   ship `std::format` integration with unit-symbol format specs. Keep `io.hpp`
   opt-in (nholthaus's I/O header alone is reported to turn a ~1 s build into
   ~11 s — paying only for included I/O is an advertisable win for us).
7. **Readable compile-time errors + a "how to read a UTL error" guide** — for a
   units library the error messages *are* the product. nholthaus, uom and
   dimensioned are all criticised for unreadable template/`typenum` dumps; Au
   markets readable errors as a headline feature. Add `static_assert` messages
   that name the offending dimensions, and put before/after error screenshots in
   the README.
8. **Honest comparison page + visibility + dogfooding** — a candid
   "UTL vs mp-units / Au / nholthaus / Boost.Units / uom" page (Au's frank
   *Alternatives* page is itself a trust-builder), one blog post or lightning
   talk, and a port of a real piece of robotics code (UTL is the successor of
   the Robotic Template Library) to find API gaps. (Was item #9.)

## Phase B — correctness moat (table stakes; opens the embedded market)

9. **Affine temperature** — a `TemperatureDelta` / point-vs-delta distinction:
   `point − point → delta`, `point + point` ill-formed, origin offsets for
   K/°C/°F. The `20 °C + 5 °C` bug is *the* canonical units example; mp-units
   (`quantity_point`), Au (`QuantityPoint`) and Boost.Units (`absolute<>`) all
   solve it — we do not. Highest-value correctness feature we are missing.
   (Was item #6.)
10. **Generic representation type beyond `float`/`double`** — support integer
    reps now and design for fixed-point, with **overflow/truncation guards**
    (the lossless-implicit / lossy-explicit rule `std::chrono` pioneered; Au's
    "overflow safety surface"). This is the gate to the embedded/robotics
    audience our header-only, fast-compile lane attracts. Boost.Units (arbitrary
    value type `Y`) and uom (`Conversion<V>`: integers, big-rationals, complex)
    lead here; we are `float`/`double` only. (Extends item #5.)
11. **Mixed-precision operations** — `Length<float> + Length<double>` promoting
    to the wider storage type via a `common_type`-style rule. (Was item #5.)
12. **Conversion-safety discipline** — a `value_cast`-style split so lossy
    conversions are explicit (or compile errors), rather than leaning on the
    accessor methods (`.m()`, `.km()`). Pairs with item #10.

## Phase C — differentiation and hedges

13. **Opt-in "kind tags"** — make the same-dimension collisions we currently
    resolve by hand (Frequency vs Activity, Angle vs SolidAngle, AbsorbedDose vs
    DoseEquivalent) systematic, without mp-units' full ISQ machinery. uom does
    this with lightweight marker traits; nholthaus and Au do not distinguish
    them at all. NOTE: distinguishing torque from energy specifically would
    reverse our deliberate "no `Torque` class" decision (N·m ≡ J) — keep that
    case optional; the `1/s` and dimensionless collisions are the defensible
    wins.
14. **Interop / upgrade path to `std::quantity`** — bidirectional conversion
    to/from raw values plus a stated "we track the standard" intent, to
    neutralise the strongest reason not to adopt a small library now
    ("I'll just wait for `std::units`"). Au markets exactly this
    "adopt now, migrate for free later" bridge.

## Long-term / reconsidered

15. **Angle as an eighth pseudo-dimension** — **DEMOTED.** This is contested
    even inside mp-units and is a breaking v3.0 change. The opt-in kind tag
    (#13) buys `Hz ≠ rad/s` and `angle ≠ dimensionless` without breaking every
    caller. Pursue only if #13 proves insufficient. Pairs with rational
    exponents (e.g. V/√Hz noise densities) if ever needed. (Was item #8.)

## Cede — out of scope by design

- **Runtime string parsing** (`"10.5 m/s"` from config/CLI/data-file metadata)
  is structurally impossible in a compile-time model; it is **LLNL/units'**
  domain. Add later only as a separate optional companion type, never inside
  `BaseUnit`.
- **Eigen / linear-algebra element-wise units** — no library in either language
  has a clean drop-in solution; high cost, low odds.
- **Full ISQ quantity-spec system** — do not compete with mp-units' scope.

## References — surveyed libraries (June 2026)

C++:

- **mp-units** — <https://github.com/mpusz/mp-units> — C++20; ISQ
  quantity-kinds (torque ≠ energy, Hz ≠ Bq), affine `quantity_point`,
  `std::format`. Reference implementation for the standardization effort
  (paper P3045, LEWG direction approved at Croydon 2026-03, targeting C++29).
- **Au** (Aurora Innovation) — <https://github.com/aurora-opensource/au> —
  C++14; conversion/overflow safety, readable errors, single-header generator,
  `QuantityPoint` affine temperatures. Candid library comparison:
  <https://aurora-opensource.github.io/au/main/alternatives/>.
- **nholthaus/units** — <https://github.com/nholthaus/units> — C++14 single
  header; the most-used C++ units library, but unreadable template errors and a
  heavy compile-time cost cap it.
- **Boost.Units** — <https://www.boost.org/doc/libs/release/libs/units/> —
  arbitrary value types, rational exponents, `absolute<>` temperatures; feature-
  dormant since ~2010 and infamous for error-message length.
- **SI** (bernedom) — <https://github.com/bernedom/SI> — C++17, header-only,
  clean prefixes; but ships no math helpers and is near-dormant.
- **LLNL/units** — <https://github.com/LLNL/units> — the runtime model: units as
  data with string parsing and measurement types. The complement to a compile-
  time library, not a competitor.

Rust:

- **uom** — <https://github.com/iliekturtles/uom> — type-level dimensions,
  storage generic over any numeric type via `Conversion<V>`, kind markers
  (distinguishes torque from energy), a `TemperatureInterval` type; the de-facto
  Rust standard (~10M downloads).
- **dimensioned** — <https://github.com/paholg/dimensioned> — type-level
  (`typenum`); mature but dormant.
- **measurements** — <https://github.com/rust-embedded-community/rust-measurements>
  — simple runtime structs over `f64`; named per-quantity types.
