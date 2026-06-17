/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_derived_current_density_test, init) {
    auto j = CurrentDensity<double>(5.0);
    EXPECT_DOUBLE_EQ(j.Apm2(), 5.0);
}

TEST(t_derived_current_density_test, from_current_and_area) {
    auto j = CurrentDensity<double>(ElectricCurrent<double>(10.0), Area<double>(2.0));
    EXPECT_DOUBLE_EQ(j.Apm2(), 5.0);
}

TEST(t_derived_current_density_test, mapped_from_division) {
    auto j = ElectricCurrent<double>(12.0) / Area<double>(3.0);
    static_assert(std::is_same_v<decltype(j), CurrentDensity<double>>, "current / area = current density");
    EXPECT_DOUBLE_EQ(j.Apm2(), 4.0);
}

TEST(t_derived_current_density_test, dim) {
    auto dim = std::array<int8_t, 8>{0, -2, 0, 1, 0, 0, 0, 0};
    EXPECT_EQ(CurrentDensity<double>::dim(), dim);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
