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
auto unit_f = utl::Unit<float>(utl::PI);
auto unit_d = utl::Unit<double>(utl::PI);
```

Mixing storage types in the same expression is allowed; the result is promoted
to the wider type (`std::common_type_t`):

```cpp
auto sum = utl::Length<float>(1.0f) + utl::Length<double>(2.0);  // Length<double>
auto d   = utl::Velocity<float>(30.0f) * utl::Time<double>(5.0); // Length<double>
auto s   = utl::Length<float>(1.5f) * 2.0;                        // Length<double>
auto f   = utl::Length<float>(1.5f) * 2;                          // Length<float>
```

## Physical constants

Predefined constants are available in `float` (`_f`) and `double` (`_d`)
variants:

| Constant | Unit |
|---|---|
| `speed_of_light_f` / `_d` | Velocity |
| `cesium_hyperfine_freq_f` / `_d` | Frequency |
| `elementary_charge_f` / `_d` | ElectricCharge |
| `planck_constant_f` / `_d` | Energy × Time |
| `boltzmann_constant_f` / `_d` | Energy / Temperature |
| `avogadro_constant_f` / `_d` | 1 / AmountOfSubstance |
| `luminous_efficacy_f` / `_d` | LuminousFlux / Power |

## Temperature differences

Temperature is affine: °C and °F have offset origins, so the *difference* of
two temperatures is a displacement, not an absolute point. `Temperature -
Temperature` therefore yields a `TemperatureDelta`, whose `degC()` / `degF()`
apply only the scale factor (never the `+273.15` / `+32` offset). Adding two
absolute temperatures is deleted; add a delta instead:

```cpp
using Temp = utl::ThermodynamicTemperature<double>;

auto d = Temp(20, Temp::TYPE::CELSIUS) - Temp(5, Temp::TYPE::CELSIUS); // TemperatureDelta
d.degC();                                                             // 15 (not -258.15)

auto warmer = Temp(20, Temp::TYPE::CELSIUS) + utl::TemperatureDelta<double>(5); // 25 °C
```

## Angles, solid angles and torque

Angle is tracked as an eighth pseudo-dimension, so `rad`, `sr` and a plain
scalar are distinct types:

```cpp
auto solid = utl::Angle<double>(2.0) * utl::Angle<double>(3.0); // SolidAngle, 6 sr
auto back  = utl::sqrt(utl::SolidAngle<double>(9.0));           // Angle, 3 rad

// luminous intensity * solid angle = luminous flux (cd * sr = lm)
auto flux = utl::LuminousIntensity<double>(60.0) * utl::SolidAngle<double>(2.0); // 120 lm

// torque (N*m = energy / angle) is a distinct type from energy
auto torque = utl::Energy<double>(10.0) / utl::Angle<double>(2.0); // Torque, 5 N*m
auto work   = torque * utl::Angle<double>(2.0);                    // Energy, 10 J

// trigonometry takes an Angle and returns a scalar
auto y = utl::sin(utl::Angle<double>(90.0, utl::Angle<double>::TYPE::DEG)); // 1.0
```

The angle exponent defaults to zero, so every other named unit and all existing
code are unaffected.

## Precise time (`utl/time_point.hpp`)

For real-time use where sub-microsecond precision matters, the opt-in
`utl/time_point.hpp` provides `TimeDuration` and `TimeStamp` — integer-native
(`int64` nanosecond) wrappers with affine semantics. They never use floating
point, so they do not lose precision the way `double` seconds do near a large
epoch.

```cpp
#include <utl/time_point.hpp>
using namespace utl;

auto dt = TimeStamp(1500000000) - TimeStamp(1000000000); // TimeDuration, 500 ms
auto later = TimeStamp(1000000000) + milliseconds(250);  // TimeStamp
// TimeStamp + TimeStamp does not compile (adding absolute times is meaningless)

auto seconds_as_double = milliseconds(1500).to_time();   // Time<double>, 1.5 s
```

Construct durations with `nanoseconds` / `microseconds` / `milliseconds` /
`seconds`, read them with `ns()` / `us()` / `ms()` / `s()` (integer counts), and
cross into the dimensional world with `to_time()`.

`utl/chrono.hpp` bridges these types to `std::chrono`:

```cpp
#include <utl/chrono.hpp>

auto d  = to_duration(std::chrono::milliseconds(250));   // TimeDuration
auto c  = to_chrono(milliseconds(250));                  // std::chrono::nanoseconds
auto ts = to_timestamp(std::chrono::steady_clock::now()); // TimeStamp
auto tp = to_chrono<std::chrono::steady_clock>(ts);       // std::chrono::time_point
```
