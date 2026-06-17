# Changelog

## Unreleased

### Added

- Readable dimension-mismatch diagnostics: adding, subtracting or comparing
  quantities of different dimensions now fails with a clear `static_assert`
  message (e.g. "utl: cannot add quantities of different dimensions") instead of
  an overload-resolution wall of "no matching operator" notes.
- Single-header amalgamation: `single_include/utl/utl.hpp`, generated from the
  multi-header tree by `tools/amalgamate.py` and kept in sync by CI, for
  zero-setup drop-in use. (The opt-in `utl/io.hpp` is not amalgamated.)
- Five more coherent derived units, each with a from-constituents constructor
  and an automatic result-type mapping: `Vergence` (1/m, diopter),
  `Density` (kg/m³), `CurrentDensity` (A/m²), `Concentration` (mol/m³) and
  `Luminance` (cd/m²). `Luminance` (cd/m²) is distinct from `Illuminance`
  (lm/m²) thanks to the angle dimension.

## v3.0.0 (2026-06-16)

### Added

- Property-based tests (`t_property`) checking algebraic identities such as
  `(a * b) / b == a` and `inv(inv(x)) == x` across randomized values, as
  regression insurance for the mapper and operators.
- README status badges (CI, docs, latest release, license, C++17).
- Release automation: pushing a `v*` tag publishes a GitHub Release with notes
  drawn from the matching `CHANGELOG.md` section
  (`tools/extract_changelog.sh`, `.github/workflows/release.yml`).
- Zero-overhead proof (`tools/check_zero_overhead.py`, run in CI for gcc and
  clang): compiles unit arithmetic and the equivalent raw arithmetic to
  assembly at `-O2` and asserts the two are byte-for-byte identical, making
  the zero-overhead claim a regression test.
- `.clang-format` codifying the house style, with a CI `format` job that fails
  on any unformatted file. clang-format is pinned so local and CI agree.
- Mixed-precision arithmetic: same-dimension `+`, `-`, the comparison operators
  and the cross-unit `*` / `/` now accept operands with different storage types
  (e.g. `Length<float> + Length<double>`) and promote the result to the wider
  type via `std::common_type_t`.
- `TemperatureDelta` type for affine-correct temperature arithmetic: a
  *difference* of temperatures is a displacement, not an absolute point, so its
  `degC()` / `degF()` apply only the scale factor and never the `+273.15` /
  `+32` offset. Supports `Delta ± Delta`, scalar `*` / `/`, unary `-`, and
  `Temperature ± Delta`.
- Packaging: a Conan recipe (`conanfile.py` with a `test_package`) and a vcpkg
  overlay port (`packaging/vcpkg/ports`), plus README install instructions for
  Conan, vcpkg and CMake FetchContent. The imported target is `utl::utl`
  everywhere.
- Angle as an eighth pseudo-dimension: `Angle` (rad) and `SolidAngle` (sr) are
  now distinct dimensions (`rad` = angle¹, `sr` = angle²), so `Angle * Angle ==
  SolidAngle`, `sqrt(SolidAngle) == Angle`, and `LuminousIntensity * SolidAngle
  == LuminousFlux`. A new `Torque` (N·m = energy/angle) is type-distinct from
  `Energy` (`Energy / Angle == Torque`, `Torque * Angle == Energy`). Added
  `sin` / `cos` / `tan` overloads that take an `Angle` and return a scalar.

### Changed (breaking)

- `BaseUnit` gained an eighth template exponent `ANGLE` (defaulted to `0`, so
  named-unit code is unaffected) and `dim()` now returns `std::array<int8_t, 8>`.
  `Angle` and `SolidAngle` are no longer dimensionless — they carry the angle
  dimension — and `LuminousFlux` (cd·sr) is now type-distinct from
  `LuminousIntensity` (cd). Code reading `dim()` as a 7-element array, or
  relying on angles comparing equal to raw scalars, must adjust.

- `ThermodynamicTemperature - ThermodynamicTemperature` now returns a
  `TemperatureDelta` (was `ThermodynamicTemperature`), and
  `ThermodynamicTemperature + ThermodynamicTemperature` is deleted: adding two
  absolute temperatures is physically meaningless. Add a `TemperatureDelta`
  instead (`temp + TemperatureDelta(5)`). Reading a temperature *difference*
  via `.degC()` / `.degF()` previously misapplied the scale offset.
- `BaseUnit` default constructor is deleted: a physical quantity is never
  undefined. Every unit must be constructed with an explicit value. Callers
  that relied on default construction (e.g. `std::map::operator[]`,
  value-initialized `std::array`) must initialize explicitly.

## v2.0.0 (2026-06-11)

### Fixed

- Header-defined physical constants violated the ODR — any project
  including `utl/utl.hpp` from two translation units failed to link.
- `virtual` on `BaseUnit::inv()` added a vtable pointer to every unit
  (`sizeof(Length<float>)` was 16 instead of 4).
- `Mass / Acceleration` returned `Force`; the physically correct
  `Mass * Acceleration` is now derived from the dimension system.
- `FAMTO` prefix typo (now `FEMTO`), `DAYS_IN_YEAR` was 356,
  truncated km-to-mile factor replaced by the exact mile definition.
- `M_PI` (POSIX) replaced with portable `utl::PI`; the library now
  builds warning-free under MSVC `/W4`.

### Changed (breaking)

- Cross-unit arithmetic is derived from dimension exponents via
  `UnitMapper` and requires `#include <utl/utl.hpp>`; single-unit
  headers no longer provide it. Hand-written per-class operators were
  removed (~800 lines).
- `TimeTemperatureUnit` renamed to `TimeUnit`, `ElectricChangeUnit`
  renamed to `ElectricChargeUnit`.
- `type()` on dimensionless results no longer yields `Angle`.
- Physical constants are `constexpr` (immutable) instead of mutable
  globals.

### Added

- Whole library is `constexpr`; unit math evaluates at compile time.
- Unit literals: `auto d = 120.0_km + 500.0_m;`
- Comparison operators, compound assignment, unary minus.
- Stream output via `utl/io.hpp`: `30 [s^-1 m]`.
- Dimension-aware `sqrt`, `pow<N>`, `abs`, `min`, `max`.
- Imperial/engineering conversions: `yd/ft/in`, `lb/oz`, `day`,
  `Wh/cal`, `hp`, `bar/atm/psi`, `mph`.
- CMake `utl::utl` INTERFACE target with install/`find_package`
  support.
- CI on gcc, clang, MSVC and ASan/UBSan, with warnings as errors.
- mdBook user guide deployed to GitHub Pages.

## v1.0.0 (2024-05-05)

Initial release.
