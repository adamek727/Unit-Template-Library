# Usage

## Construction and conversion

Units are constructed from their base SI value and converted through named
accessors:

```cpp
auto length = utl::Length<float>(1500);
std::cout << length.km() << std::endl;

auto area = utl::Area<float>(6543);
std::cout << area.m2() << std::endl;
```

## Arithmetic with predefined operators

Common physical relations are available directly:

```cpp
auto v = utl::Velocity<float>(30);
auto t = utl::Time<float>(5);
auto d = v * t;
std::cout << "Distance: " << d.m() << " m" << std::endl;

auto g = utl::Acceleration<float>(9.81);
auto tt = utl::Time<float>(10);
auto s = 0.5 * g * tt * tt;
std::cout << "Free fall: " << s.m() << " m" << std::endl;
```

## Arbitrary dimensional expressions

Any dimensionally valid expression maps back to its named unit
automatically. Combinations without a named SI unit yield the raw
`BaseUnit`, which still tracks dimensions and exposes `value()`:

```cpp
auto m = utl::Mass<float>(1);
auto &c = utl::speed_of_light_f;
auto e = m * c * c;
std::cout << "Energy: " << e.J() << " J" << std::endl;
```

## Unit literals

The `utl::literals` namespace provides double-precision literal
suffixes for common units:

```cpp
using namespace utl::literals;

auto distance = 120.0_km + 500.0_m;
auto speed = distance / 2.0_h;
if (speed > 50.0_kmph) {
    std::cout << "Speeding: " << speed.kmph() << " km/h" << std::endl;
}
```

Available suffixes: `_s`, `_ms`, `_min`, `_h`, `_m`, `_km`, `_mm`,
`_kg`, `_g`, `_A`, `_K`, `_mol`, `_cd`, `_mps`, `_kmph`, `_N`, `_J`,
`_W`, `_Hz`, `_Pa`, `_V`, `_rad`.

## Comparisons and compound assignment

Units of the same dimension support `==`, `!=`, `<`, `<=`, `>`, `>=`
as well as `+=`, `-=`, scalar `*=`, `/=` and unary minus.

## Stream output

Including `utl/io.hpp` enables printing any unit as its value followed
by its SI dimensions:

```cpp
#include <utl/io.hpp>

std::cout << utl::Velocity<float>(30) << std::endl;  // 30 [s^-1 m]
```

## Precision selection

Every unit is templated on its storage type:

```cpp
auto unit_f = utl::Unit<float>(M_PI);
auto unit_d = utl::Unit<double>(M_PI);
```

## Physical constants

Predefined constants are available in `float` (`_f`) and `double` (`_d`)
variants:

| Constant | Unit |
|---|---|
| `speed_of_light_f` / `_d` | Velocity |
| `cesium_hyperfine_freq_f` / `_d` | Frequency |
| `elementary_charge_f` / `_d` | ElectricCharge |
| `planc_constant_f` / `_d` | Energy × Time |
| `boltzmann_constant_f` / `_d` | Energy / Temperature |
| `avogadro_constant_f` / `_d` | 1 / AmountOfSubstance |
| `luminous_efficacy_f` / `_d` | LuminousFlux / Power |
