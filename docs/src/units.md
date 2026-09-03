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
| `Concentration` | [mol/m³] |
| `Conductance` | siemens [S] |
| `CurrentDensity` | [A/m²] |
| `Density` | [kg/m³] |
| `DoseEquivalent` | sievert [Sv] |
| `ElectricCharge` | coulomb [C] |
| `Energy` | joule [J] |
| `Force` | newton [N] |
| `Frequency` | hertz [Hz] |
| `Illuminance` | lux [lx] |
| `Inductance` | henry [H] |
| `Luminance` | [cd/m²] |
| `LuminousFlux` | lumen [lm] |
| `MagneticFlux` | weber [Wb] |
| `MagneticFluxDensity` | tesla [T] |
| `Power` | watt [W] |
| `Pressure` | pascal [Pa] |
| `SolidAngle` | steradian [sr] |
| `Torque` | newton-metre [N·m] (energy / angle) |
| `Velocity` | [m/s] |
| `Vergence` | [1/m] (diopter) |
| `Voltage` | volt [V] |
| `Volume` | [m³] |

## Units sharing a dimension signature

Several SI units share the same dimension exponents. Each still gets its own
type and its own automatic result-type mapping, because `BaseUnit` carries a
*kind tag* next to the exponents: a type parameter that defaults to `void` and
that two quantities must share before they can be added, subtracted or
compared. A mismatch is a compile-time error with a readable message.

| Dimensions | Default kind | Tagged kind |
|---|---|---|
| 1/s | `Frequency` | `Activity` |
| m²/s² | `AbsorbedDose` | `DoseEquivalent` |
| K | `ThermodynamicTemperature` | `TemperatureDelta` |

The tag is not a dimension: multiplying or dividing by another unit, `inv()`,
`sqrt` and `pow` drop it, so `Activity * Time` is a plain dimensionless count
and `Energy / TemperatureDelta` is the same quantity as `Energy / Temperature`.

## The angle pseudo-dimension

An eighth exponent tracks angle (`rad` = angle¹, `sr` = angle²), so `Angle`,
`SolidAngle` and a dimensionless scalar are now distinct, and `LuminousFlux`
(cd·sr) is distinct from `LuminousIntensity` (cd) — both get their own mapped
result type instead of colliding. The exponent defaults to zero, so every other
unit and all existing code are unchanged.

This is also what makes `Torque` (N·m = energy / angle) a type distinct from
`Energy` (J): `Energy / Angle == Torque` and `Torque * Angle == Energy`, while a
plain `Force * Length` still maps to `Energy`.
