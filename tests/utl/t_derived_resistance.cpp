/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/resistance.hpp"
#include "utl/derived/conductance.hpp"

using namespace utl;

TEST(t_resistance_test, init) {
    auto resistance_1 = Resistance<float>(5.0);
    EXPECT_FLOAT_EQ(resistance_1.MOhm(), 0.000005f);
    EXPECT_FLOAT_EQ(resistance_1.kOhm(), 0.005f);
    EXPECT_FLOAT_EQ(resistance_1.Ohm(), 5.0f);
    EXPECT_FLOAT_EQ(resistance_1.mOhm(), 5000.0f);

    auto resistance_2 = Resistance<float>(Voltage<float>(6), ElectricCurrent<float>(2));
    EXPECT_FLOAT_EQ(resistance_2.Ohm(), 3.0f);
}

TEST(t_resistance_test, add) {
    auto resistance_1 = Resistance<float>(5.0);
    auto resistance_2 = Resistance<float>(10.0);
    EXPECT_FLOAT_EQ((resistance_1 + resistance_2).Ohm(), 15);
}

TEST(t_resistance_test, sub) {
    auto resistance_1 = Resistance<float>(15.0);
    auto resistance_2 = Resistance<float>(10.0);
    EXPECT_FLOAT_EQ((resistance_1 - resistance_2).Ohm(), 5);
}

TEST(t_resistance_test, scalar_mul_div) {
    auto resistance_1 = Resistance<float>(6.0);
    auto resistance_2 = 2 * resistance_1 * 2;
    EXPECT_FLOAT_EQ(resistance_2.Ohm(), 24);
    auto resistance_3 = resistance_1 / 2;
    EXPECT_FLOAT_EQ(resistance_3.Ohm(), 3);
}

TEST(t_resistance_test, mul) {
    auto resistance_1 = Resistance<float>(6.0);
    auto el_cur_1 = ElectricCurrent<float>(3);
    auto voltage_1 = resistance_1 * el_cur_1;
    EXPECT_FLOAT_EQ(voltage_1.V(), 18);
}

TEST(t_resistance_test, inv) {
    auto resistance_1 = Resistance<float>(6.0);
    EXPECT_FLOAT_EQ(resistance_1.inv().type().S(), 1.0 / 6.0);
}

TEST(t_mass_test, dim) {
    auto dim = std::array<int8_t, 7>{-3, 2, 1, -2, 0, 0, 0};
    EXPECT_EQ(Resistance<float>::dim(), dim);
    EXPECT_EQ(Resistance<float>::TimeDim(), -3);
    EXPECT_EQ(Resistance<float>::LengthDim(), 2);
    EXPECT_EQ(Resistance<float>::MassDim(), 1);
    EXPECT_EQ(Resistance<float>::ElCurrDim(), -2);
    EXPECT_EQ(Resistance<float>::TdTempDim(), 0);
    EXPECT_EQ(Resistance<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Resistance<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}