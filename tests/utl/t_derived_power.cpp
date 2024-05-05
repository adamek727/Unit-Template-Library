/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/power.hpp"

using namespace utl;

TEST(t_power_test, init) {
    auto power_1 = Power<float>(10000);
    EXPECT_FLOAT_EQ(power_1.W(), 10000.0f);
    EXPECT_FLOAT_EQ(power_1.kW(), 10.0);

    auto power_2 = Power<float>(Energy<float>(5), Time<float>(2));
    EXPECT_FLOAT_EQ(power_2.W(), 2.5f);
}

TEST(t_power_test, add) {
    auto power_1 = Power<float>(5.0);
    auto power_2 = Power<float>(10.0);
    EXPECT_FLOAT_EQ((power_1 + power_2).W(), 15);
}

TEST(t_power_test, sub) {
    auto power_1 = Power<float>(15.0);
    auto power_2 = Power<float>(10.0);
    EXPECT_FLOAT_EQ((power_1 - power_2).W(), 5);
}

TEST(t_power_test, scalar_mul_div) {
    auto power_1 = Power<float>(6.0);
    auto power_2 = 2 * power_1 * 2;
    EXPECT_FLOAT_EQ(power_2.W(), 24);
    auto power_3 = power_1 / 2;
    EXPECT_FLOAT_EQ(power_3.W(), 3);
}

TEST(t_power_test, mul) {
    auto power_1 = Power<float>(6.0);
    auto time_1 = Time<float>(2.0);
    auto energy_1 = power_1 * time_1;
    EXPECT_FLOAT_EQ(energy_1.J(), 12);
}

TEST(t_power_test, div) {
    auto power_1 = Power<float>(6.0);
    auto energy_1 = Energy<float>(2.0);
    auto freq_1 = power_1 / energy_1;
    EXPECT_FLOAT_EQ(freq_1.Hz(), 3);
}

TEST(t_power_test, dim) {
    auto dim = std::array<int8_t, 7>{-3, 2, 1, 0, 0, 0, 0};
    EXPECT_EQ(Power<float>::dim(), dim);
    EXPECT_EQ(Power<float>::TimeDim(), -3);
    EXPECT_EQ(Power<float>::LengthDim(), 2);
    EXPECT_EQ(Power<float>::MassDim(), 1);
    EXPECT_EQ(Power<float>::ElCurrDim(), 0);
    EXPECT_EQ(Power<float>::TdTempDim(), 0);
    EXPECT_EQ(Power<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Power<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}