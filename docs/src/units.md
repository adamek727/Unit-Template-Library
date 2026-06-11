# Units Reference

All units are templates over the storage type, e.g. `Length<float>` or
`Length<double>`. Shorthand aliases with `_f` and `_d` suffixes exist for
every unit, e.g. `Length_f`, `Length_d`.

## Base units

| Unit | SI unit | Example accessors |
|---|---|---|
| `Time` | second [s] | `s()`, `ms()`, `us()`, `ns()`, `min()`, `h()` |
| `Length` | meter [m] | `m()`, `km()`, `mm()`, `um()`, `nm()`, `mi()` |
| `Mass` | kilogram [kg] | `kg()`, `g()`, `mg()`, `ug()`, `tonne()` |
| `ElectricCurrent` | ampere [A] | `A()` |
| `ThermodynamicTemperature` | kelvin [K] | `K()`, `degC()`, `degF()` |
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
| `Velocity` | [m/s] |
| `Voltage` | volt [V] |
| `Volume` | [m³] |

## Dimensionless quantities

`Angle` and `SolidAngle` are both dimensionless in the seven-exponent SI
system. The generic `type()` mapping for dimensionless results resolves to
`Angle`; construct `SolidAngle` explicitly when needed.
