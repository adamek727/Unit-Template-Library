# Future Work

Roadmap after v2.0.0, roughly in value order.

## Near-term (v2.1)

1. **Badges and release automation** — CI/docs/release badges in the
   README; a workflow that turns a pushed tag into a GitHub Release
   with notes taken from `CHANGELOG.md`.
2. **clang-format and a format check in CI** — lock the code style
   before external contributions arrive.
3. **Zero-overhead proof in CI** — a check comparing the generated
   assembly of unit arithmetic against raw float arithmetic, turning
   the zero-overhead claim into a regression test.
4. **Property-based tests** — algebraic identities such as
   `(a * b) / b == a` and `inv(inv(x)) == x` across randomized values;
   cheap insurance against mapper regressions.

## Medium-term (v2.x)

5. **Mixed-precision operations** — `Length<float> + Length<double>`
   does not compile today; promote to the wider storage type.
6. **Temperature deltas** — `Temp - Temp` returning an absolute
   temperature is physically wrong (affine unit). A separate
   `TemperatureDelta` type prevents the classic `20 degC + 5 K` bug
   class.
7. **Packaging** — vcpkg and Conan submissions; the biggest adoption
   lever for a header-only library.

## Long-term (v3.0)

8. **Angle as an eighth pseudo-dimension** — solves the dimension
   collision table at the root: rad != sr != dimensionless,
   Hz != rad/s, and torque (N·m) becomes distinguishable from energy
   (J). Breaking change, hence a major version. Pairs naturally with
   rational exponents (e.g. V/sqrt(Hz) noise densities) if ever
   needed.

## Non-code

9. **Dogfooding and visibility** — port a piece of real robotics code
   to UTL (the library is the successor of the Robotic Template
   Library); real usage finds API gaps faster than review. Then
   announce (r/cpp, awesome-cpp).
