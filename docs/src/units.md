# Units Reference

All units are templates over the storage type, e.g. `Length<float>` or
`Length<double>`. Shorthand aliases with `_f` and `_d` suffixes exist for
every unit, e.g. `Length_f`, `Length_d`.

## Base units

| Unit | SI unit | Example accessors |
|---|---|---|
| `Time` | second [s] | `s()`, `ms()`, `us()`, `ns()`, `min()`, `h()`, `day()` |
| `Length` | meter [m] | `m()`, `km()`, `mm()`, `um()`, `nm()`, `mi()`, `yd()`, `ft()`, `in()` |
| `Mass` | kilogram [kg] | `kg()`, `g()`, `mg()`, `ug()`, `tonne()`, `lb()`, `oz()` |
| `ElectricCurrent` | ampere [A] | `A()` |
| `ThermodynamicTemperature` | kelvin [K] | `K()`, `degC()`, `degF()` |
| `TemperatureDelta` | kelvin [K] (a *difference*) | `K()`, `degC()`, `degF()` (offset-free) |
| `AmountOfSubstance` | mole [mol] | `mol()` |
| `LuminousIntensity` | candela [cd] | `cd()` |

## Derived units

| Unit | SI unit |
|---|---|
| `AbsorbedDose` | gray [Gy] |
| `Acceleration` | [m/s²] |
| `Activity` | becquerel [Bq] |
| `Angle` | radian [rad] |
| `Area` | [m²] |
| `Capacitance` | farad [F] |
| `CatalyticActivity` | katal [kat] |
| `Conductance` | siemens [S] |
| `DoseEquivalent` | sievert [Sv] |
| `ElectricCharge` | coulomb [C] |
| `Energy` | joule [J] |
| `Force` | newton [N] |
| `Frequency` | hertz [Hz] |
| `Illuminance` | lux [lx] |
| `Inductance` | henry [H] |
| `LuminousFlux` | lumen [lm] |
| `MagneticFlux` | weber [Wb] |
| `MagneticFluxDensity` | tesla [T] |
| `Power` | watt [W] |
| `Pressure` | pascal [Pa] |
| `SolidAngle` | steradian [sr] |
| `Torque` | newton-metre [N·m] (energy / angle) |
| `Velocity` | [m/s] |
| `Voltage` | volt [V] |
| `Volume` | [m³] |

## Units sharing a dimension signature

Several SI units share the same dimension exponents, so automatic
result-type mapping has to pick one winner; construct the other
explicitly when needed:

| Dimensions | Mapped result | Construct explicitly |
|---|---|---|
| 1/s | `Frequency` | `Activity` |
| m²/s² | `AbsorbedDose` | `DoseEquivalent` |
| K | `ThermodynamicTemperature` | `TemperatureDelta` |

## The angle pseudo-dimension

An eighth exponent tracks angle (`rad` = angle¹, `sr` = angle²), so `Angle`,
`SolidAngle` and a dimensionless scalar are now distinct, and `LuminousFlux`
(cd·sr) is distinct from `LuminousIntensity` (cd) — both get their own mapped
result type instead of colliding. The exponent defaults to zero, so every other
unit and all existing code are unchanged.

This is also what makes `Torque` (N·m = energy / angle) a type distinct from
`Energy` (J): `Energy / Angle == Torque` and `Torque * Angle == Energy`, while a
plain `Force * Length` still maps to `Energy`.
