/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/voltage.hpp"

using namespace utl;

TEST(t_voltage_test, init) {
    auto voltage_1 = Voltage<float>(5.0);
    EXPECT_FLOAT_EQ(voltage_1.V(), 5.0f);
    EXPECT_FLOAT_EQ(voltage_1.kV(), 0.005f);
    EXPECT_FLOAT_EQ(voltage_1.mV(), 5000.0f);

    auto voltage_2 = Voltage<float>(Power<float>(6), ElectricCurrent<float>(2));
    EXPECT_FLOAT_EQ(voltage_2.V(), 3);
}

TEST(t_voltage_test, add) {
    auto voltage_1 = Voltage<float>(5.0);
    auto voltage_2 = Voltage<float>(10.0);
    EXPECT_FLOAT_EQ((voltage_1 + voltage_2).V(), 15);
}

TEST(t_voltage_test, sub) {
    auto voltage_1 = Voltage<float>(15.0);
    auto voltage_2 = Voltage<float>(10.0);
    EXPECT_FLOAT_EQ((voltage_1 - voltage_2).V(), 5);
}

TEST(t_voltage_test, scalar_mul_div) {
    auto voltage_1 = Voltage<float>(6.0);
    auto voltage_2 = 2 * voltage_1 * 2;
    EXPECT_FLOAT_EQ(voltage_2.V(), 24);
    auto voltage_3 = voltage_1 / 2;
    EXPECT_FLOAT_EQ(voltage_3.V(), 3);
}

TEST(t_voltage_test, mul) {
    auto voltage_1 = Voltage<float>(15.0);
    auto el_cur_1 = ElectricCurrent<float>(5.0);
    auto power_1 = voltage_1 * el_cur_1;
    EXPECT_FLOAT_EQ(power_1.W(), 75.0);

}

TEST(t_voltage_test, dim) {
    auto dim = std::array<int8_t, 7>{-3, 2, 1, -1, 0, 0, 0};
    EXPECT_EQ(Voltage<float>::dim(), dim);
    EXPECT_EQ(Voltage<float>::TimeDim(), -3);
    EXPECT_EQ(Voltage<float>::LengthDim(), 2);
    EXPECT_EQ(Voltage<float>::MassDim(), 1);
    EXPECT_EQ(Voltage<float>::ElCurrDim(), -1);
    EXPECT_EQ(Voltage<float>::TdTempDim(), 0);
    EXPECT_EQ(Voltage<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Voltage<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}