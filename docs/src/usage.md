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

## Arithmetic without predefined operators

Any dimensionally valid expression can be computed through the raw
dimension-tracking layer. `raw()` exposes the underlying `BaseUnit` and
`type()` maps the result back to its named unit:

```cpp
auto m = utl::Mass<float>(1);
auto &c = utl::speed_of_light_f;
auto e = (m.raw() * c.raw() * c.raw()).type();
std::cout << "Energy: " << e.J() << " J" << std::endl;
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
