/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/length.hpp"

using namespace utl;

TEST(t_length_test, init) {
    auto length_1 = Length<float>(5.0);
    EXPECT_FLOAT_EQ(length_1.m(), 5.0f);
    EXPECT_FLOAT_EQ(length_1.km(), 0.005f);
    EXPECT_FLOAT_EQ(length_1.mi(), 0.003106856);
    EXPECT_FLOAT_EQ(length_1.mm(), 5000.0f);
    EXPECT_FLOAT_EQ(length_1.um(), 5000000.0f);
    EXPECT_FLOAT_EQ(length_1.nm(), 5000000000.0f);
}

TEST(t_length_test, add) {
    auto length_1 = Length<float>(5.0);
    auto length_2 = Length<float>(10.0);
    EXPECT_FLOAT_EQ((length_1 + length_2).m(), 15);
}

TEST(t_length_test, sub) {
    auto length_1 = Length<float>(15.0);
    auto length_2 = Length<float>(10.0);
    EXPECT_FLOAT_EQ((length_1 - length_2).m(), 5);
}

TEST(t_length_test, scalar_mul_div) {
    auto length_1 = Length<float>(6.0);
    auto length_2 = 2 * length_1 * 2;
    EXPECT_FLOAT_EQ(length_2.m(), 24);
    auto length_3 = length_1 / 2;
    EXPECT_FLOAT_EQ(length_3.m(), 3);
}

TEST(t_length_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 1, 0, 0, 0, 0, 0};
    EXPECT_EQ(Length<float>::dim(), dim);
    EXPECT_EQ(Length<float>::TimeDim(), 0);
    EXPECT_EQ(Length<float>::LengthDim(), 1);
    EXPECT_EQ(Length<float>::MassDim(), 0);
    EXPECT_EQ(Length<float>::ElCurrDim(), 0);
    EXPECT_EQ(Length<float>::TdTempDim(), 0);
    EXPECT_EQ(Length<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Length<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}