/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include "utl/utl.hpp"

int main() {
    auto bad = utl::Frequency<double>(1.0) + utl::Activity<double>(1.0);
    return 0;
}
