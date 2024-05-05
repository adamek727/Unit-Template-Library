/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/electric_current.hpp"

using namespace utl;

TEST(t_electric_current_test, init) {
    auto el_cur_1 = ElectricCurrent<float>(5.0);
    EXPECT_FLOAT_EQ(el_cur_1.A(), 5.0f);
    EXPECT_FLOAT_EQ(el_cur_1.mA(), 5000.0f);
    EXPECT_FLOAT_EQ(el_cur_1.uA(), 5000000.0f);
    EXPECT_FLOAT_EQ(el_cur_1.nA(), 5000000000.0f);
}

TEST(t_electric_current_test, add) {
    auto el_cur_1 = ElectricCurrent<float>(5.0);
    auto el_cur_2 = ElectricCurrent<float>(10.0);
    EXPECT_FLOAT_EQ((el_cur_1 + el_cur_2).A(), 15);
}

TEST(t_electric_current_test, sub) {
    auto el_cur_1 = ElectricCurrent<float>(15.0);
    auto el_cur_2 = ElectricCurrent<float>(10.0);
    EXPECT_FLOAT_EQ((el_cur_1 - el_cur_2).A(), 5);
}

TEST(t_electric_current_test, scalar_mul_div) {
    auto el_cur_1 = ElectricCurrent<float>(6.0);
    auto el_cur_2 = 2 * el_cur_1 * 2;
    EXPECT_FLOAT_EQ(el_cur_2.A(), 24);
    auto el_cur_3 = el_cur_1 / 2;
    EXPECT_FLOAT_EQ(el_cur_3.A(), 3);
}

TEST(t_electric_current_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 1, 0, 0, 0};
    EXPECT_EQ(ElectricCurrent<float>::dim(), dim);
    EXPECT_EQ(ElectricCurrent<float>::TimeDim(), 0);
    EXPECT_EQ(ElectricCurrent<float>::LengthDim(), 0);
    EXPECT_EQ(ElectricCurrent<float>::MassDim(), 0);
    EXPECT_EQ(ElectricCurrent<float>::ElCurrDim(), 1);
    EXPECT_EQ(ElectricCurrent<float>::TdTempDim(), 0);
    EXPECT_EQ(ElectricCurrent<float>::AmOfSubDim(), 0);
    EXPECT_EQ(ElectricCurrent<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}