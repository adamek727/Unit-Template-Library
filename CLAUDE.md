# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Commands

```bash
# Configure + build (ENABLE_WERROR=1 mirrors CI; warnings fail the build)
cmake -B build -DENABLE_TESTS=1 -DENABLE_EXAMPLES=1 -DENABLE_WERROR=1
cmake --build build -j

# All tests / a single test (each test file is its own binary)
ctest --test-dir build --output-on-failure
ctest --test-dir build -R t_base_length        # or: ./build/tests/t_base_length

# Example binary
./build/examples/usage_example

# Zero-overhead proof (raw vs unit arithmetic must emit identical asm at -O2)
python3 tools/check_zero_overhead.py g++        # or clang++

# Format (CI fails on unformatted files; pin matches .github/workflows/ci.yml)
clang-format -i $(find include tests examples \( -name '*.hpp' -o -name '*.cpp' \))

# User guide (deployed to GitHub Pages from main)
mdbook build docs
```

GTest comes from the system package or, when absent, a FetchContent fallback in
`tests/CMakeLists.txt`. New test files go in `tests/utl/t_*.cpp` (with their own
`main`) and are registered with `make_units_test(<name>)` in
`tests/CMakeLists.txt`. "Must not compile" cases go in `tests/compile_fail/cf_*.cpp`
and are registered with `make_compile_fail_test(<name> "<expected message>")`:
the test builds the snippet on its own and passes only when the compiler output
matches the message, so a snippet that compiles, or fails for another reason,
fails the test.

## Architecture

Header-only C++17 library in `include/utl/`. Everything is `constexpr` except
stream output (`io.hpp`). `t_constexpr` and a `sizeof` test in `t_base_unit`
guard the compile-time and zero-overhead guarantees.

The dimension system, and how result types are derived:

- `BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE>`
  (`base/base_unit.hpp`) encodes the seven SI exponents plus an eighth angle
  pseudo-dimension (`rad` = angle¹, `sr` = angle²) as `int8_t` template
  parameters. `ANGLE` defaults to `0`, so 7-argument aliases and all named-unit
  code keep working. A tenth parameter, `typename KIND = void`, is a kind tag
  (see below): not a dimension, not in `dim()`, but part of the type. The only
  data member is the value. That exponent order is
  used everywhere — aliases, `dim()` (an 8-element array), operators, `io.hpp`
  symbols.
- **A physical quantity is never undefined**: `BaseUnit() = delete`, so no
  unit is default-constructible. Construction always takes an explicit value.
  Do not add default constructors back (not to `BaseUnit`, not to named
  units); fix callers instead — `insert_or_assign` over `map::operator[]`,
  explicit element init for `std::array`, initialized struct members.
- Each named unit derives from a **literal-exponent** alias
  (`using ForceUnit = BaseUnit<T, -2, 1, 1, 0, 0, 0, 0>`) and registers itself
  via a `UnitMapper<ForceUnit<T>>` specialization. Keep aliases literal:
  defining them through other unit classes (the old
  `MulBaseUnits<T, Force<T>, Length<T>>` style) causes template instantiation
  cycles when mapper matching evaluates them.
- `mapped_unit_t<U>` resolves to the registered named unit, or to `U` itself
  when no mapper exists.
- Cross-dimension `*` and `/` are **free operators** in `operators.hpp`,
  included last by `utl.hpp` so every mapper is visible. Their result type is
  `mapped_unit_t` of the combined exponents — `Velocity * Time` returns
  `Length`, unmapped combinations return raw `BaseUnit`. Do **not** add
  hand-written cross-unit operators to unit classes; dimensional arithmetic is
  derived. Consequence: cross-unit arithmetic needs `#include <utl/utl.hpp>`,
  not individual unit headers.
- Same-dimension `+`, `-`, comparisons, compound assignment and scalar ops are
  `BaseUnit` members that also return the mapped type. `+`, `-` and the
  comparisons are templated on the other operand's scalar type, so mixed
  precision (`Length<float> + Length<double>`) promotes to `std::common_type_t`
  of the two; cross-unit `*` / `/` in `operators.hpp` promote the same way. Those
  members accept an operand of any dimension and `static_assert` that the
  exponents match, so a dimension mismatch yields a readable message rather than
  "no matching operator" spew.

Kind tags — units sharing an exponent signature would otherwise fight over the
mapper. The tenth `BaseUnit` parameter `KIND` resolves that: each colliding unit
derives from an alias with its own empty tag struct
(`BaseUnit<T, -1, 0, 0, 0, 0, 0, 0, 0, ActivityKind>`), registers its own mapper
and needs no hand-written operators. Same-dimension operators (`+`, `-`,
comparisons, scalar `*` / `/`, `abs` / `min` / `max`) require equal kinds and
`static_assert` a readable "different kinds" message; dimension-changing ones
(cross-unit `*` / `/`, `inv`, `sqrt`, `pow`) drop the kind, so `Bq * s` is a
plain dimensionless count and `J / ΔK` is the same quantity as `J / K`.

| Signature | Default kind | Tagged kind |
|---|---|---|
| 1/s | `Frequency` | `Activity` (`ActivityKind`) |
| m²/s² | `AbsorbedDose` | `DoseEquivalent` (`DoseEquivalentKind`) |
| K | `ThermodynamicTemperature` | `TemperatureDelta` (`TemperatureDeltaKind`) |

`ThermodynamicTemperature` is affine and keeps hand-written members:
`Temp - Temp` → `TemperatureDelta`, `Temp ± Delta` → `Temp`, and `Temp + Temp` /
`Temp += Temp` are deleted.

The angle pseudo-dimension resolved two former collisions: `Angle` (angle¹),
`SolidAngle` (angle²) and dimensionless are now distinct and all mapped, and
`LuminousFlux` (cd·sr = `[cd, angle²]`) is now distinct from `LuminousIntensity`
(cd) and gets its own mapper.

The photometric chain (`LuminousFlux`/`Illuminance`) is fully derived: with the
angle dimension, `LuminousFlux / SolidAngle → LuminousIntensity`,
`LuminousFlux / Area → Illuminance` and `Illuminance * Area → LuminousFlux` all
come from `operators.hpp` plus the mappers, so those classes carry no operators
of their own. A member operator hides the base-class ones — and with them mixed
precision and the readable mismatch diagnostics — so if a class must add one,
re-expose the rest with `using XxxUnit<T>::operator*;`. `Torque`
(N·m = energy/angle, i.e. `[…, angle⁻¹]`) is type-distinct from `Energy` (J):
`Energy / Angle == Torque` and `Torque * Angle == Energy`, while `Force * Length`
still yields `Energy`. Angle-aware `sin`/`cos`/`tan` (in `angle.hpp`) take an
`Angle` and return a scalar.

Top-level headers: `literals.hpp` (`utl::literals`, double-based suffixes),
`math.hpp` (`sqrt` halves exponents — odd exponents are a compile error —
`pow<N>`, `abs`, `min`, `max`), `io.hpp` (opt-in `operator<<`), `utl.hpp`
(constants like `speed_of_light_d`, `_f`/`_d` aliases, includes everything).

## Conventions

- TDD is the norm here: write the failing test first; for compile-time API the
  RED phase is a compile error.
- CI runs gcc, clang, MSVC (`/W4`) and an ASan/UBSan job, all with warnings as
  errors. MSVC discipline: every `double`→`T` narrowing needs an explicit
  `static_cast` (conversion accessors return `static_cast<T>(...)`); float test
  literals need an `f` suffix unless exactly representable; use `utl::PI`,
  never `M_PI`.
- Breaking changes go to `CHANGELOG.md`; releases are semver tags with the
  version mirrored in `CMakeLists.txt` and `CITATION.cff`. Pushing a `v*` tag
  triggers `release.yml`, which publishes a GitHub Release with notes taken
  from the matching `CHANGELOG.md` section (so add that section before tagging).
  The roadmap lives in `FUTURE_WORK.md`.
