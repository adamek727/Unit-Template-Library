# Unit Template Library

[![CI](https://github.com/adamek727/Unit-Template-Library/actions/workflows/ci.yml/badge.svg)](https://github.com/adamek727/Unit-Template-Library/actions/workflows/ci.yml)
[![Docs](https://github.com/adamek727/Unit-Template-Library/actions/workflows/docs.yml/badge.svg)](https://adamek727.github.io/Unit-Template-Library/)
[![Release](https://img.shields.io/github/v/release/adamek727/Unit-Template-Library?sort=semver)](https://github.com/adamek727/Unit-Template-Library/releases)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](License.txt)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

Easy to use header-only library to represent type-safety SI units.

## Authors and feedback

For technical feedback, bug reporting, feature proposition etc. please use the GitHub issue system. Opening issues allows all of us to participate on the solution, library related things are kept with its repository and other users may benefit from our communication as well.

 - Adam Ligocki ligocki.a@gmail.com

The library is successor of the [Robotic Template Library](https://github.com/Robotics-BUT/Robotic-Template-Library).

## Design Principles

### A physical quantity is never undefined

Every unit must be constructed with an explicit value; default construction
is deleted on `BaseUnit` and therefore on every named unit:

```
Length<float> a;            // does not compile
auto b = Length<float>(2);  // ok: 2 meters
```

A default-constructed quantity would have to pick a value out of thin air
(zero, garbage, NaN) and silently flow through computations. That is the same
class of bug the dimensional type system exists to prevent, just on the value
axis instead of the dimension axis. Holding units in containers therefore
requires explicit initialization: use `std::map::insert_or_assign` instead of
`operator[]`, fill `std::array` elements explicitly, and give struct members
an initial value where the struct itself is default-constructed.

## Usage Example

### Code example

```
#include <utl/utl.hpp>

// Definition and unit conversion
auto a = Area<float>(6543);
std::cout << "Area: " << a.m2() << std::endl;

// Operations with predefined operators
auto v = Velocity<float>(30); // mps
auto t = Time<float>(5);
auto d = v * t;
std::cout << "Distance: " << d.m() << "m" << std::endl;

auto g = Acceleration<float>(9.81);
auto tt = Time<float>(10);
auto s = 0.5 * g * tt * tt;
std::cout << "Free fall: " << s.m() << "m" << std::endl;

// Any dimensionally valid expression maps back to its named unit.
auto m = Mass<float>(1);
auto &c = speed_of_light_f;
auto e = m * c * c;
std::cout << "Energy: " << e.J() << "J" << std::endl;

// Precision selection
auto unit_f = Unit<float>(PI);
auto unit_d = Unit<double>(PI);
std::cout << std::fixed << std::setprecision(18) << "float: " << unit_f.value() << " double: " << unit_d.value() << std::endl;

// Unit literals (double precision)
using namespace utl::literals;
auto distance = 120.0_km + 500.0_m;
auto speed = distance / 2.0_h;
if (speed > 50.0_kmph) {
    std::cout << "Speeding: " << speed.kmph() << " km/h" << std::endl;
}

// Stream output (requires #include <utl/io.hpp>)
std::cout << speed << std::endl;  // prints "16.7361 [s^-1 m]"
```

### Angles, solid angles and torque

Angle is tracked as an eighth pseudo-dimension, so `rad`, `sr` and a plain
scalar are distinct types and the dimension system relates them:

```
// rad * rad = sr,  sqrt(sr) = rad
auto solid = Angle<double>(2.0) * Angle<double>(3.0);   // SolidAngle, 6 sr
auto back  = sqrt(SolidAngle<double>(9.0));             // Angle, 3 rad

// luminous intensity * solid angle = luminous flux (cd * sr = lm)
auto flux = LuminousIntensity<double>(60.0) * SolidAngle<double>(2.0); // 120 lm

// torque is N*m = energy / angle, and is NOT the same type as energy
auto torque = Energy<double>(10.0) / Angle<double>(2.0);  // Torque, 5 N*m
auto work   = torque * Angle<double>(2.0);                // Energy, 10 J

// trigonometry takes an Angle and returns a scalar
auto y = sin(Angle<double>(90.0, Angle<double>::TYPE::DEG)); // 1.0
```

Because the angle exponent defaults to zero, every other named unit
(`Length`, `Force`, …) and all existing code are unaffected.

### Add to Existing Project

```
git submodule add https://github.com/adamek727/Unit-Template-Library libs/utl/
git submodule init
git submodule update --recursive
```

and in your CMakeLists.txt file add

```cmake
add_subdirectory(libs/utl)
target_link_libraries(your_target utl::utl)
```

Alternatively install the library (`cmake -B build && cmake --install build`)
and use `find_package(utl REQUIRED)`.

#### CMake FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(utl
        GIT_REPOSITORY https://github.com/adamek727/Unit-Template-Library
        GIT_TAG v3.0.0)
FetchContent_MakeAvailable(utl)
target_link_libraries(your_target utl::utl)
```

#### Conan

A header-only recipe ships in `conanfile.py`. Until the package is on Conan
Center, export it locally:

```
conan create .
```

then depend on `unit-template-library/3.0.0` and link `utl::utl`.

#### vcpkg

An overlay port lives in `packaging/vcpkg/ports`. Install with:

```
vcpkg install unit-template-library --overlay-ports=packaging/vcpkg/ports
```

#### Single header

For a zero-setup drop-in, copy the amalgamated header
`single_include/utl/utl.hpp` into your project and include it directly:

```cpp
#include <utl/utl.hpp>
```

It is generated from the multi-header tree by `tools/amalgamate.py` (CI keeps it
in sync). The opt-in stream output (`utl/io.hpp`) is not part of the
amalgamation.

In all cases the imported target is `utl::utl` and headers are included as
`#include <utl/utl.hpp>`.

### Documentation

The user guide is published at
https://adamek727.github.io/Unit-Template-Library/ and lives in `docs/`
(built with [mdBook](https://rust-lang.github.io/mdBook/)).

### Run Examples

To make just a brief overview and to make the examples work, clone this repo and run following commands.
```
git clone https://github.com/adamek727/Unit-Template-Library
cd Unit-Template-Library/
mkdir build
cd build
cmake .. -DENABLE_EXAMPLES=1
make -j4
```

### Run Tests

To evaluate tests, run:
```
git clone https://github.com/adamek727/Unit-Template-Library
cd Unit-Template-Library/
mkdir build
cd build
cmake .. -DENABLE_TESTS=1
make -j4
ctest
```

## Inspiration:

 - https://github.com/wardw/simpleunit/tree/master
 - https://github.com/mpusz/mp-units
 - https://docs.wpilib.org/en/stable/docs/software/basic-programming/cpp-units.html
 - https://www.youtube.com/watch?v=o0ck5eqpOLc

## Reference

If you find this library useful, please mention it in the README of your project, or cite it.

## License

MIT License

Copyright (c) 2024 Adam Ligocki

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.