/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include "utl/utl.hpp"

int main() {
    auto bad = utl::Length<double>(1.0) + utl::Time<double>(1.0);
    return 0;
}
