/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/conductance.hpp"

using namespace utl;

TEST(t_conductance_test, init) {
    auto conductance_1 = Conductance<float>(5.0);
    EXPECT_FLOAT_EQ(conductance_1.S(), 5.0f);

    auto conductance_2 = Conductance<float>(ElectricCurrent<float>(6), Voltage<float>(3));
    EXPECT_FLOAT_EQ(conductance_2.S(), 2.0f);
}

TEST(t_conductance_test, add) {
    auto conductance_1 = Conductance<float>(5.0);
    auto conductance_2 = Conductance<float>(10.0);
    EXPECT_FLOAT_EQ((conductance_1 + conductance_2).S(), 15);
}

TEST(t_conductance_test, sub) {
    auto conductance_1 = Conductance<float>(15.0);
    auto conductance_2 = Conductance<float>(10.0);
    EXPECT_FLOAT_EQ((conductance_1 - conductance_2).S(), 5);
}

TEST(t_conductance_test, scalar_mul_div) {
    auto conductance_1 = Conductance<float>(6.0);
    auto conductance_2 = 2 * conductance_1 * 2;
    EXPECT_FLOAT_EQ(conductance_2.S(), 24);
    auto conductance_3 = conductance_1 / 2;
    EXPECT_FLOAT_EQ(conductance_3.S(), 3);
}

TEST(t_conductance_test, mul) {
    auto conductance_1 = Conductance<float>(6.0);
    auto voltage_1 = Voltage<float>(3);
    auto el_cur_1 = conductance_1 * voltage_1;
    EXPECT_FLOAT_EQ(el_cur_1.A(), 18);
}

TEST(t_conductance_test, inv) {
    auto conductance_1 = Conductance<float>(1.0 / 6.0);
    EXPECT_FLOAT_EQ(conductance_1.inv().type().Ohm(), 6.0);
}

TEST(t_mass_test, dim) {
    auto dim = std::array<int8_t, 7>{3, -2, -1, 2, 0, 0, 0};
    EXPECT_EQ(Conductance<float>::dim(), dim);
    EXPECT_EQ(Conductance<float>::TimeDim(), 3);
    EXPECT_EQ(Conductance<float>::LengthDim(), -2);
    EXPECT_EQ(Conductance<float>::MassDim(), -1);
    EXPECT_EQ(Conductance<float>::ElCurrDim(), 2);
    EXPECT_EQ(Conductance<float>::TdTempDim(), 0);
    EXPECT_EQ(Conductance<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Conductance<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}