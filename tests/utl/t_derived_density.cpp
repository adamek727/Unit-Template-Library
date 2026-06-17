/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_derived_density_test, init) {
    auto d = Density<double>(1000.0);
    EXPECT_DOUBLE_EQ(d.kgpm3(), 1000.0);
}

TEST(t_derived_density_test, from_mass_and_volume) {
    auto d = Density<double>(Mass<double>(2.0), Volume<double>(0.5));
    EXPECT_DOUBLE_EQ(d.kgpm3(), 4.0);
}

TEST(t_derived_density_test, mapped_from_division) {
    auto d = Mass<double>(10.0) / Volume<double>(2.0);
    static_assert(std::is_same_v<decltype(d), Density<double>>, "mass / volume = density");
    EXPECT_DOUBLE_EQ(d.kgpm3(), 5.0);
}

TEST(t_derived_density_test, dim) {
    auto dim = std::array<int8_t, 8>{0, -3, 1, 0, 0, 0, 0, 0};
    EXPECT_EQ(Density<double>::dim(), dim);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
