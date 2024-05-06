/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <iostream>
#include <iomanip>
#include "utl/utl.hpp"

using namespace utl;

int main(int, char*[]) {

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

    return 0;
}