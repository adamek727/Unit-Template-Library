# Unit Template Library

Easy to use header-only library to represent type-safety SI units.

## Authors and feedback

For technical feedback, bug reporting, feature proposition etc. please use the GitHub issue system. Opening issues allows all of us to participate on the solution, library related things are kept with its repository and other users may benefit from our communication as well.

 - Adam Ligocki ligocki.a@gmail.com

The library is successor of the [Robotic Template Library](https://github.com/Robotics-BUT/Robotic-Template-Library).

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

// Operations without predefined operators.
auto m = Mass<float>(1);
auto &c = speed_of_light_f;
auto e = (m.raw() * c.raw() * c.raw()).type();
std::cout << "Energy: " << e.J() << "J" << std::endl;

// Precision selection
auto unit_f = Unit<float>(M_PI);
auto unit_d = Unit<double>(M_PI);
std::cout << std::fixed << std::setprecision(18) << "float: " << unit_f.value() << " double: " << unit_d.value() << std::endl;
```

### Add to Existing Project

```
git submodule add https://github.com/adamek727/Unit-Template-Library libs/utl/
git submodule init
git submodule update --recursive
```

and in your CMakeLists.txt file add

```
include_directories(libs/utl/include/)
```

Now you are able to include UTL headers into you code.

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