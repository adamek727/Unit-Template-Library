/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_derived_luminance_test, init) {
    auto l = Luminance<double>(300.0);
    EXPECT_DOUBLE_EQ(l.cdpm2(), 300.0);
}

TEST(t_derived_luminance_test, from_intensity_and_area) {
    auto l = Luminance<double>(LuminousIntensity<double>(60.0), Area<double>(2.0));
    EXPECT_DOUBLE_EQ(l.cdpm2(), 30.0);
}

TEST(t_derived_luminance_test, mapped_from_division) {
    auto l = LuminousIntensity<double>(100.0) / Area<double>(4.0);
    static_assert(std::is_same_v<decltype(l), Luminance<double>>, "luminous intensity / area = luminance (distinct from illuminance)");
    EXPECT_DOUBLE_EQ(l.cdpm2(), 25.0);
}

TEST(t_derived_luminance_test, dim) {
    auto dim = std::array<int8_t, 8>{0, -2, 0, 0, 0, 0, 1, 0};
    EXPECT_EQ(Luminance<double>::dim(), dim);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
