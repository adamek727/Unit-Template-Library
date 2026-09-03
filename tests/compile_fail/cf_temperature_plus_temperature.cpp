/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include "utl/utl.hpp"

int main() {
    auto bad = utl::ThermodynamicTemperature<double>(1.0) + utl::ThermodynamicTemperature<double>(2.0);
    return 0;
}
