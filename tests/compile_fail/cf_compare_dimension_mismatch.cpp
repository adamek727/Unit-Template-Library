/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include "utl/utl.hpp"

int main() {
    return utl::Length<double>(1.0) < utl::Mass<double>(1.0) ? 1 : 0;
}
