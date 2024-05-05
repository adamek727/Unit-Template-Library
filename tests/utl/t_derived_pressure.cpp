/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/pressure.hpp"

using namespace utl;

TEST(t_pressure_test, init) {
    auto pressure_1 = Pressure<float>(50000);
    EXPECT_FLOAT_EQ(pressure_1.Pa(), 50000.0f);
    EXPECT_FLOAT_EQ(pressure_1.hPa(), 500.0f);
    EXPECT_FLOAT_EQ(pressure_1.kPa(), 50.0f);

    auto pressure_2 = Pressure<float>(Force<float>(15), Area<float>(3));
    EXPECT_FLOAT_EQ(pressure_2.Pa(), 5.0f);

}

TEST(t_pressure_test, add) {
    auto pressure_1 = Pressure<float>(5.0);
    auto pressure_2 = Pressure<float>(10.0);
    EXPECT_FLOAT_EQ((pressure_1 + pressure_2).Pa(), 15);
}

TEST(t_pressure_test, sub) {
    auto pressure_1 = Pressure<float>(15.0);
    auto pressure_2 = Pressure<float>(10.0);
    EXPECT_FLOAT_EQ((pressure_1 - pressure_2).Pa(), 5);
}

TEST(t_pressure_test, scalar_mul_div) {
    auto pressure_1 = Force<float>(6.0);
    auto pressure_2 = 2 * pressure_1 * 2;
    EXPECT_FLOAT_EQ(pressure_2.N(), 24);
    auto pressure_3 = pressure_1 / 2;
    EXPECT_FLOAT_EQ(pressure_3.N(), 3);
}

TEST(t_pressure_test, mul) {
    auto pressure_1 = Pressure<float>(6.0);
    auto area_1 = Area<float>(2.0);
    auto force_1 = pressure_1 * area_1;
    EXPECT_FLOAT_EQ(force_1.N(), 12);
}

TEST(t_pressure_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, -1, 1, 0, 0, 0, 0};
    EXPECT_EQ(Pressure<float>::dim(), dim);
    EXPECT_EQ(Pressure<float>::TimeDim(), -2);
    EXPECT_EQ(Pressure<float>::LengthDim(), -1);
    EXPECT_EQ(Pressure<float>::MassDim(), 1);
    EXPECT_EQ(Pressure<float>::ElCurrDim(), 0);
    EXPECT_EQ(Pressure<float>::TdTempDim(), 0);
    EXPECT_EQ(Pressure<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Pressure<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}