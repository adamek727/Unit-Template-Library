/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/electric_charge.hpp"

using namespace utl;

TEST(t_el_charge_test, init) {
    auto el_charge_1 = ElectricCharge<float>(15);
    EXPECT_FLOAT_EQ(el_charge_1.C(), 15.0f);

    auto el_charge_2 = ElectricCharge<float>(ElectricCurrent<float>(5), Time<float>(2));
    EXPECT_FLOAT_EQ(el_charge_2.C(), 10.0f);
}

TEST(t_el_charge_test, add) {
    auto el_charge_1 = ElectricCharge<float>(5.0);
    auto el_charge_2 = ElectricCharge<float>(10.0);
    EXPECT_FLOAT_EQ((el_charge_1 + el_charge_2).C(), 15);
}

TEST(t_el_charge_test, sub) {
    auto el_charge_1 = ElectricCharge<float>(15.0);
    auto el_charge_2 = ElectricCharge<float>(10.0);
    EXPECT_FLOAT_EQ((el_charge_1 - el_charge_2).C(), 5);
}

TEST(t_el_charge_test, scalar_mul_div) {
    auto el_charge_1 = ElectricCharge<float>(6.0);
    auto el_charge_2 = 2 * el_charge_1 * 2;
    EXPECT_FLOAT_EQ(el_charge_2.C(), 24);
    auto el_charge_3 = el_charge_1 / 2;
    EXPECT_FLOAT_EQ(el_charge_3.C(), 3);
}

TEST(t_el_charge_test, div) {
    auto el_charge_1 = ElectricCharge<float>(6.0);

    auto el_cur_1 = ElectricCurrent<float>(2.0);
    auto time_1 = el_charge_1 / el_cur_1;
    EXPECT_FLOAT_EQ(time_1.s(), 3);

    auto time_2 = Time<float>(3.0);
    auto el_cur_2 = el_charge_1 / time_2;
    EXPECT_FLOAT_EQ(el_cur_2.A(), 2);
}

TEST(t_el_charge_test, dim) {
    auto dim = std::array<int8_t, 7>{1, 0, 0, 1, 0, 0, 0};
    EXPECT_EQ(ElectricCharge<float>::dim(), dim);
    EXPECT_EQ(ElectricCharge<float>::TimeDim(), 1);
    EXPECT_EQ(ElectricCharge<float>::LengthDim(), 0);
    EXPECT_EQ(ElectricCharge<float>::MassDim(), 0);
    EXPECT_EQ(ElectricCharge<float>::ElCurrDim(), 1);
    EXPECT_EQ(ElectricCharge<float>::TdTempDim(), 0);
    EXPECT_EQ(ElectricCharge<float>::AmOfSubDim(), 0);
    EXPECT_EQ(ElectricCharge<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}