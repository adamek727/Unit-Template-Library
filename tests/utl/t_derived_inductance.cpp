/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/inductance.hpp"

using namespace utl;

TEST(t_inductance_test, init) {
    auto inductance_1 = Inductance<float>(5.0);
    EXPECT_FLOAT_EQ(inductance_1.H(), 5.0f);
    auto inductance_2 = Inductance<float>(MagneticFlux<float>(6), ElectricCurrent<float>(2));
    EXPECT_FLOAT_EQ(inductance_2.H(), 3.0f);
}

TEST(t_inductance_test, add) {
    auto inductance_1 = Inductance<float>(5.0);
    auto inductance_2 = Inductance<float>(10.0);
    EXPECT_FLOAT_EQ((inductance_1 + inductance_2).H(), 15);
}

TEST(t_inductance_test, sub) {
    auto inductance_1 = Inductance<float>(15.0);
    auto inductance_2 = Inductance<float>(10.0);
    EXPECT_FLOAT_EQ((inductance_1 - inductance_2).H(), 5);
}

TEST(t_inductance_test, scalar_mul_div) {
    auto inductance_1 = Inductance<float>(6.0);
    auto inductance_2 = 2 * inductance_1 * 2;
    EXPECT_FLOAT_EQ(inductance_2.H(), 24);
    auto inductance_3 = inductance_1 / 2;
    EXPECT_FLOAT_EQ(inductance_3.H(), 3);
}

TEST(t_inductance_test, mul) {
    auto inductance_1 = Inductance<float>(6);
    auto el_curr_1 = ElectricCurrent<float>(2);
    auto mag_flux_1 = inductance_1 * el_curr_1;
    EXPECT_FLOAT_EQ(mag_flux_1.Wb(), 12);
}

TEST(t_inductance_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, 2, 1, -2, 0, 0, 0};
    EXPECT_EQ(Inductance<float>::dim(), dim);
    EXPECT_EQ(Inductance<float>::TimeDim(), -2);
    EXPECT_EQ(Inductance<float>::LengthDim(), 2);
    EXPECT_EQ(Inductance<float>::MassDim(), 1);
    EXPECT_EQ(Inductance<float>::ElCurrDim(), -2);
    EXPECT_EQ(Inductance<float>::TdTempDim(), 0);
    EXPECT_EQ(Inductance<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Inductance<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
