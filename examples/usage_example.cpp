/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <iostream>
#include <iomanip>
#include "utl/utl.hpp"
#include "utl/io.hpp"

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

    auto g = Acceleration<float>(9.81f);
    auto tt = Time<float>(10);
    auto s = 0.5 * g * tt * tt;
    std::cout << "Free fall: " << s.m() << "m" << std::endl;

    // Any dimensionally valid expression maps back to its named unit.
    auto m = Mass<float>(1);
    auto &c = speed_of_light_f;
    auto e = m * c * c;
    std::cout << "Energy: " << e.J() << "J" << std::endl;

    // Precision selection
    auto unit_f = Unit<float>(static_cast<float>(PI));
    auto unit_d = Unit<double>(PI);
    std::cout << std::fixed << std::setprecision(18) << "float: " << unit_f.value() << " double: " << unit_d.value() << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout << std::setprecision(6);

    // Unit literals (double precision)
    using namespace utl::literals;
    auto distance = 120.0_km + 500.0_m;
    auto speed = distance / 2.0_h;
    if (speed > 50.0_kmph) {
        std::cout << "Speeding: " << speed.kmph() << " km/h" << std::endl;
    }

    // Stream output
    std::cout << "Speed: " << speed << std::endl;

    return 0;
}