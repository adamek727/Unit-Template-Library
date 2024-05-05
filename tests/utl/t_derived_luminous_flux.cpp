/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/luminous_flux.hpp"
#include "utl/derived/illuminance.hpp"

using namespace utl;

TEST(t_luminous_flux_test, init) {
    auto lum_flux_1 = LuminousFlux<float>(100);
    EXPECT_FLOAT_EQ(lum_flux_1.lm(), 100.0f);

    auto lum_flux_2 = LuminousFlux<float>(LuminousIntensity<float>(60), SolidAngle<float>(2));
    EXPECT_FLOAT_EQ(lum_flux_2.lm(), 120.0f);
}

TEST(t_luminous_flux_test, add) {
    auto lum_flux_1 = LuminousFlux<float>(5.0);
    auto lum_flux_2 = LuminousFlux<float>(10.0);
    EXPECT_FLOAT_EQ((lum_flux_1 + lum_flux_2).lm(), 15);
}

TEST(t_luminous_flux_test, sub) {
    auto lum_flux_1 = LuminousFlux<float>(15.0);
    auto lum_flux_2 = LuminousFlux<float>(10.0);
    EXPECT_FLOAT_EQ((lum_flux_1 - lum_flux_2).lm(), 5);
}

TEST(t_luminous_flux_test, scalar_mul_div) {
    auto lum_flux_1 = LuminousFlux<float>(6.0);
    auto lum_flux_2 = 2 * lum_flux_1 * 2;
    EXPECT_FLOAT_EQ(lum_flux_2.lm(), 24);
    auto lum_flux_3 = lum_flux_1 / 2;
    EXPECT_FLOAT_EQ(lum_flux_3.lm(), 3);
}

TEST(t_luminous_flux_test, div) {
    auto lum_flux_1 = LuminousFlux<float>(10.0);
    auto solid_angle_1 = SolidAngle<float>(5.0);
    auto lum_int_1 = LuminousIntensity<float>(2.0);
    auto area_1 = Area<float>(20.0);

    auto solid_angle_2 = lum_flux_1 / lum_int_1;
    EXPECT_FLOAT_EQ(solid_angle_2.sr(), 5.0);

    auto lum_int_2 = lum_flux_1 / solid_angle_1;
    EXPECT_FLOAT_EQ(lum_int_2.cd(), 2.0);

    auto illuminance_1 = lum_flux_1 / area_1;
    EXPECT_FLOAT_EQ(illuminance_1.lux(), 0.5);
}

TEST(t_luminous_flux_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 0, 0, 0, 1};
    EXPECT_EQ(LuminousFlux<float>::dim(), dim);
    EXPECT_EQ(LuminousFlux<float>::TimeDim(), 0);
    EXPECT_EQ(LuminousFlux<float>::LengthDim(), 0);
    EXPECT_EQ(LuminousFlux<float>::MassDim(), 0);
    EXPECT_EQ(LuminousFlux<float>::ElCurrDim(), 0);
    EXPECT_EQ(LuminousFlux<float>::TdTempDim(), 0);
    EXPECT_EQ(LuminousFlux<float>::AmOfSubDim(), 0);
    EXPECT_EQ(LuminousFlux<float>::LumIntDim(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}