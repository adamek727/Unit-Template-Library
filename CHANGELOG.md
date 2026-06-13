# Changelog

## Unreleased

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

### Changed (breaking)

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
