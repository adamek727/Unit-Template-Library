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

## Next (v3.x, incremental and non-breaking)

- **Readable dimension-mismatch errors** — an `enable_if` / `static_assert`
  layer so a bad `Length + Time` reports "cannot add Length and Time" instead of
  template-overload spew. Biggest day-to-day ergonomic win.
- **`std::format` / `fmt` formatter** — a formatter specialization with format
  specs (precision, symbol style), beyond the existing `operator<<`.
- **Fill the stubbed derived units** — vergence (1/m), density (kg/m³), current
  density (A/m²), concentration (mol/m³), luminance (cd/m²); each a small PR.
- **Single-header amalgamation** — generate one `utl_single.hpp` in CI for
  drop-in use and godbolt demos.

## v4.0.0 — affine quantities and precise time

A themed major release around the point-vs-displacement model that
`TemperatureDelta` already introduced.

- **`TimeStamp` and `TimeDuration`** — `TimeStamp` is an affine *point* on the
  time axis (epoch-relative absolute time); its difference is a displacement:
  `TimeStamp − TimeStamp → TimeDuration`, `TimeStamp + TimeDuration → TimeStamp`,
  `TimeStamp + TimeStamp` deleted, and `TimeStamp` does **not** take part in
  cross-unit `*` / `/`. Useful for real-time applications where precise timing
  matters. (`Time<T>` is already an offset-free duration, so `TimeDuration` is
  likely a clarifying alias/sibling of `Time`; decide distinct-type vs alias.)
- **High-precision / integer storage** — `double` seconds lose sub-microsecond
  resolution at Unix-epoch magnitude, so a precise `TimeStamp` wants integer
  storage (e.g. `int64_t` nanoseconds, like `std::chrono` / `timespec`). This
  generalizes `BaseUnit` beyond floating-point storage and is the breaking part
  that warrants a major version.
- **Generalized affine model** — factor the point/displacement machinery into a
  reusable `Absolute<Unit>`; `TemperatureDelta`/`Temperature` and
  `TimeDuration`/`TimeStamp` become the first two instances, and positions vs
  displacements follow the same shape.
- **`std::chrono` interop** — `TimeStamp` ↔ `std::chrono::time_point`,
  `TimeDuration` ↔ `std::chrono::duration`; the natural bridge to real code.

## Later / bigger bets

- **Rational exponents** — e.g. `V/sqrt(Hz)` noise densities; pairs naturally
  with the angle dimension already in place.
- **Scaled storage** — keep `km` as `km` in the type (a scale factor) to avoid
  precision loss versus always-SI storage.
- **Vector quantities / Eigen interop** — `Vector3<Length<T>>` or quantities
  over Eigen; most robotics math is vectors, and UTL is the Robotic Template
  Library's successor.
