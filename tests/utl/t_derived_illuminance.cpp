/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/illuminance.hpp"

using namespace utl;

TEST(t_illuminance_test, init) {
    auto illuminance_1 = Illuminance<float>(100);
    EXPECT_FLOAT_EQ(illuminance_1.lux(), 100.0f);

    auto illuminance_2 = Illuminance<float>(LuminousFlux<float>(60), Area<float>(10));
    EXPECT_FLOAT_EQ(illuminance_2.lux(), 6);
}

TEST(t_illuminance_test, add) {
    auto illuminance_1 = Illuminance<float>(5.0);
    auto illuminance_2 = Illuminance<float>(10.0);
    EXPECT_FLOAT_EQ((illuminance_1 + illuminance_2).lux(), 15);
}

TEST(t_illuminance_test, sub) {
    auto illuminance_1 = Illuminance<float>(15.0);
    auto illuminance_2 = Illuminance<float>(10.0);
    EXPECT_FLOAT_EQ((illuminance_1 - illuminance_2).lux(), 5);
}

TEST(t_illuminance_test, scalar_mul_div) {
    auto illuminance_1 = Illuminance<float>(6.0);
    auto illuminance_2 = 2 * illuminance_1 * 2;
    EXPECT_FLOAT_EQ(illuminance_2.lux(), 24);
    auto illuminance_3 = illuminance_1 / 2;
    EXPECT_FLOAT_EQ(illuminance_3.lux(), 3);
}

TEST(t_illuminance_test, mul) {
    auto illuminance_1 = Illuminance<float>(15.0);
    auto area_1 = Area<float>(5.0);

    auto lum_flux = illuminance_1 * area_1;
    EXPECT_FLOAT_EQ(lum_flux.lm(), 75.0);
}

TEST(t_illuminance_test, dim) {
    auto dim = std::array<int8_t, 7>{0, -2, 0, 0, 0, 0, 1};
    EXPECT_EQ(Illuminance<float>::dim(), dim);
    EXPECT_EQ(Illuminance<float>::TimeDim(), 0);
    EXPECT_EQ(Illuminance<float>::LengthDim(), -2);
    EXPECT_EQ(Illuminance<float>::MassDim(), 0);
    EXPECT_EQ(Illuminance<float>::ElCurrDim(), 0);
    EXPECT_EQ(Illuminance<float>::TdTempDim(), 0);
    EXPECT_EQ(Illuminance<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Illuminance<float>::LumIntDim(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}