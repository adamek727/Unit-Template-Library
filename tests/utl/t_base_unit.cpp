/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/base_unit.hpp"

using namespace utl;

using TestUnit = BaseUnit<float, 1, 2, 3, 4, 5, 6, 7>;

TEST(t_unit_test, add) {
    auto unit_t_1 = TestUnit(1);
    auto unit_t_2 = TestUnit(2);
    auto unit_t_3 = unit_t_1 + unit_t_2;
    EXPECT_FLOAT_EQ(unit_t_3.value(), 3);
    EXPECT_EQ(unit_t_3.TimeDim(), 1);
    EXPECT_EQ(unit_t_3.LengthDim(), 2);
    EXPECT_EQ(unit_t_3.MassDim(), 3);
    EXPECT_EQ(unit_t_3.ElCurrDim(), 4);
    EXPECT_EQ(unit_t_3.TdTempDim(), 5);
    EXPECT_EQ(unit_t_3.AmOfSubDim(), 6);
    EXPECT_EQ(unit_t_3.LumIntDim(), 7);
}

TEST(t_unit_test, sub) {
    auto unit_t_1 = TestUnit(1);
    auto unit_t_2 = TestUnit(2);
    auto unit_t_3 = unit_t_1 - unit_t_2;
    EXPECT_FLOAT_EQ(unit_t_3.value(), -1);
    EXPECT_EQ(unit_t_3.TimeDim(), 1);
    EXPECT_EQ(unit_t_3.LengthDim(), 2);
    EXPECT_EQ(unit_t_3.MassDim(), 3);
    EXPECT_EQ(unit_t_3.ElCurrDim(), 4);
    EXPECT_EQ(unit_t_3.TdTempDim(), 5);
    EXPECT_EQ(unit_t_3.AmOfSubDim(), 6);
    EXPECT_EQ(unit_t_3.LumIntDim(), 7);
}

TEST(t_time_test, scalar_mul_div) {
    auto time_1 = TestUnit(6.0);
    auto time_2 = 2 * time_1 * 2;
    EXPECT_FLOAT_EQ(time_2.value(), 24);
    auto time_3 = time_1 / 2;
    EXPECT_FLOAT_EQ(time_3.value(), 3);
}

TEST(t_unit_test, mul) {
    auto unit_t_1 = TestUnit(2);
    auto unit_t_2 = TestUnit(3);
    auto unit_t_3 = unit_t_1 * unit_t_2;
    EXPECT_FLOAT_EQ(unit_t_3.value(), 6);
    EXPECT_EQ(unit_t_3.TimeDim(), 2);
    EXPECT_EQ(unit_t_3.LengthDim(), 4);
    EXPECT_EQ(unit_t_3.MassDim(), 6);
    EXPECT_EQ(unit_t_3.ElCurrDim(), 8);
    EXPECT_EQ(unit_t_3.TdTempDim(), 10);
    EXPECT_EQ(unit_t_3.AmOfSubDim(), 12);
    EXPECT_EQ(unit_t_3.LumIntDim(), 14);
}

TEST(t_unit_test, div) {
    auto unit_t_1 = TestUnit(6);
    auto unit_t_2 = TestUnit(2);
    auto unit_t_3 = unit_t_1 / unit_t_2;
    EXPECT_FLOAT_EQ(unit_t_3.value(), 3);
    EXPECT_EQ(unit_t_3.TimeDim(), 0);
    EXPECT_EQ(unit_t_3.LengthDim(), 0);
    EXPECT_EQ(unit_t_3.MassDim(), 0);
    EXPECT_EQ(unit_t_3.ElCurrDim(), 0);
    EXPECT_EQ(unit_t_3.TdTempDim(), 0);
    EXPECT_EQ(unit_t_3.AmOfSubDim(), 0);
    EXPECT_EQ(unit_t_3.LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}