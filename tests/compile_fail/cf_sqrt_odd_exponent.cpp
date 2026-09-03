/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include "utl/utl.hpp"

int main() {
    auto bad = utl::sqrt(utl::Length<double>(4.0));
    return 0;
}
