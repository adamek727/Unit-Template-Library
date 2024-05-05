/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/luminous_intensity.hpp"

using namespace utl;

TEST(t_luminous_intensity_test, init) {
    auto lum_int_1 = LuminousIntensity<float>(5.0);
    EXPECT_FLOAT_EQ(lum_int_1.cd(), 5.0f);
}

TEST(t_luminous_intensity_test, add) {
    auto lum_int_1 = LuminousIntensity<float>(5.0);
    auto lum_int_2 = LuminousIntensity<float>(10.0);
    EXPECT_FLOAT_EQ((lum_int_1 + lum_int_2).cd(), 15);
}

TEST(t_luminous_intensity_test, sub) {
    auto lum_int_1 = LuminousIntensity<float>(15.0);
    auto lum_int_2 = LuminousIntensity<float>(10.0);
    EXPECT_FLOAT_EQ((lum_int_1 - lum_int_2).cd(), 5);
}

TEST(t_luminous_intensity_test, scalar_mul_div) {
    auto lum_int_1 = LuminousIntensity<float>(6.0);
    auto lum_int_2 = 2 * lum_int_1 * 2;
    EXPECT_FLOAT_EQ(lum_int_2.cd(), 24);
    auto lum_int_3 = lum_int_1 / 2;
    EXPECT_FLOAT_EQ(lum_int_3.cd(), 3);
}

TEST(t_luminous_intensity_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 0, 0, 0, 1};
    EXPECT_EQ(LuminousIntensity<float>::dim(), dim);
    EXPECT_EQ(LuminousIntensity<float>::TimeDim(), 0);
    EXPECT_EQ(LuminousIntensity<float>::LengthDim(), 0);
    EXPECT_EQ(LuminousIntensity<float>::MassDim(), 0);
    EXPECT_EQ(LuminousIntensity<float>::ElCurrDim(), 0);
    EXPECT_EQ(LuminousIntensity<float>::TdTempDim(), 0);
    EXPECT_EQ(LuminousIntensity<float>::AmOfSubDim(), 0);
    EXPECT_EQ(LuminousIntensity<float>::LumIntDim(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}