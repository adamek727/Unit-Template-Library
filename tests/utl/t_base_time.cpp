/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/time.hpp"
#include "utl/derived/frequency.hpp"

using namespace utl;

TEST(t_time_test, init) {
    auto time = Time<float>(3600.0);
    EXPECT_FLOAT_EQ(time.s(), 3600.0f);
    EXPECT_FLOAT_EQ(time.h(), 1.0f);
    EXPECT_FLOAT_EQ(time.min(), 60.0f);
    EXPECT_FLOAT_EQ(time.ms(), 3600000.0f);
    EXPECT_FLOAT_EQ(time.us(), 3600000000.0f);
    EXPECT_FLOAT_EQ(time.ns(), 3600000000000.0f);
}

TEST(t_time_test, add) {
    auto time_1 = Time<float>(5.0);
    auto time_2 = Time<float>(10.0);
    EXPECT_FLOAT_EQ((time_1 + time_2).s(), 15);
}

TEST(t_time_test, sub) {
    auto time_1 = Time<float>(15.0);
    auto time_2 = Time<float>(10.0);
    EXPECT_FLOAT_EQ((time_1 - time_2).s(), 5);
}

TEST(t_time_test, scalar_mul_div) {
    auto time_1 = Time<float>(6.0);
    auto time_2 = 2 * time_1 * 2;
    EXPECT_FLOAT_EQ(time_2.s(), 24);
    auto time_3 = time_1 / 2;
    EXPECT_FLOAT_EQ(time_3.s(), 3);
}

TEST(t_time_test, inv) {
    auto time_1 = Time<float>(5.0);
    auto freq_1 = time_1.inv().type();
    EXPECT_FLOAT_EQ(freq_1.Hz(), 0.2);
}

TEST(t_time_test, dim) {
    auto dim = std::array<int8_t, 7>{1, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(Time<float>::dim(), dim);
    EXPECT_EQ(Time<float>::TimeDim(), 1);
    EXPECT_EQ(Time<float>::LengthDim(), 0);
    EXPECT_EQ(Time<float>::MassDim(), 0);
    EXPECT_EQ(Time<float>::ElCurrDim(), 0);
    EXPECT_EQ(Time<float>::TdTempDim(), 0);
    EXPECT_EQ(Time<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Time<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}