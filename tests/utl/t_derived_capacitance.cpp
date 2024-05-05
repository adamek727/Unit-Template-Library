/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/capacitance.hpp"

using namespace utl;

TEST(t_cap_test, init) {
    auto cap_1 = Capacitance<float>(5.0);
    EXPECT_FLOAT_EQ(cap_1.F(), 5.0f);
    EXPECT_FLOAT_EQ(cap_1.mF(), 5000.0f);
    EXPECT_FLOAT_EQ(cap_1.uF(), 5000000.0f);
    EXPECT_FLOAT_EQ(cap_1.nF(), 5000000000.0f);
    EXPECT_FLOAT_EQ(cap_1.pF(), 5000000000000.0f);
}

TEST(t_cap_test, add) {
    auto cap_1 = Capacitance<float>(5.0);
    auto cap_2 = Capacitance<float>(10.0);
    EXPECT_FLOAT_EQ((cap_1 + cap_2).F(), 15);
}

TEST(t_cap_test, sub) {
    auto cap_1 = Capacitance<float>(15.0);
    auto cap_2 = Capacitance<float>(10.0);
    EXPECT_FLOAT_EQ((cap_1 - cap_2).F(), 5);
}

TEST(t_cap_test, scalar_mul_div) {
    auto cap_1 = Capacitance<float>(6.0);
    auto cap_2 = 2 * cap_1 * 2;
    EXPECT_FLOAT_EQ(cap_2.F(), 24);
    auto cap_3 = cap_1 / 2;
    EXPECT_FLOAT_EQ(cap_3.F(), 3);
}

TEST(t_cap_test, mul) {
    auto cap_1 = Capacitance<float>(6.0);
    auto voltage_1 = Voltage<float>(3);
    auto el_charge = cap_1 * voltage_1;
    EXPECT_FLOAT_EQ(el_charge.C(), 18);
}

TEST(t_mass_test, dim) {
    auto dim = std::array<int8_t, 7>{4, -2, -1, 2, 0, 0, 0};
    EXPECT_EQ(Capacitance<float>::dim(), dim);
    EXPECT_EQ(Capacitance<float>::TimeDim(), 4);
    EXPECT_EQ(Capacitance<float>::LengthDim(), -2);
    EXPECT_EQ(Capacitance<float>::MassDim(), -1);
    EXPECT_EQ(Capacitance<float>::ElCurrDim(), 2);
    EXPECT_EQ(Capacitance<float>::TdTempDim(), 0);
    EXPECT_EQ(Capacitance<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Capacitance<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}