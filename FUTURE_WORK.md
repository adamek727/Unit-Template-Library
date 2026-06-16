# Future Work

## Delivered

The post-v2.0.0 roadmap shipped across v2.x and v3.0.0:

1. **Badges and release automation** — README badges and a tag-triggered
   GitHub Release workflow (`release.yml`).
2. **clang-format and a CI format check** — `.clang-format` plus a pinned CI
   `format` job.
3. **Zero-overhead proof in CI** — `tools/check_zero_overhead.py` diffs the
   generated assembly of unit vs raw arithmetic for gcc and clang.
4. **Property-based tests** — algebraic identities (`(a * b) / b == a`,
   `inv(inv(x)) == x`) across randomized values (`t_property`).
5. **Mixed-precision operations** — `Length<float> + Length<double>` promotes to
   the wider storage type via `std::common_type_t`.
6. **Temperature deltas** — `TemperatureDelta` makes `Temp - Temp` affine-correct
   and forbids `Temp + Temp`.
7. **Packaging** — Conan recipe (`conanfile.py`) and a vcpkg overlay port
   (`packaging/vcpkg/ports`).
8. **Angle as an eighth pseudo-dimension** (v3.0.0, breaking) — `rad` ≠ `sr` ≠
   dimensionless, `LuminousFlux` ≠ `LuminousIntensity`, and a `Torque` type
   distinct from `Energy`, plus angle-aware `sin`/`cos`/`tan`.

## Remaining

9. **Dogfooding and visibility** — port a piece of real robotics code to UTL
   (the library is the successor of the Robotic Template Library); real usage
   finds API gaps faster than review. Then announce (r/cpp, awesome-cpp).

## Possible future directions

- **Rational exponents** — e.g. `V/sqrt(Hz)` noise densities; pairs naturally
  with the angle dimension already in place.
- Vergence, density, current density, concentration, luminance and the other
  derived units stubbed out in `derived/all.hpp`.
