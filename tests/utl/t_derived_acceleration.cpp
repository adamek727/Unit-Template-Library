/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/acceleration.hpp"

using namespace utl;

TEST(t_acceleration_test, init) {

    auto acc_1 = Acceleration<float>(5.0);
    EXPECT_FLOAT_EQ(acc_1.mps2(), 5.0f);

    auto acc_2 = Acceleration<float>(Velocity<float>(6), Time<float>(2));
    EXPECT_FLOAT_EQ(acc_2.mps2(), 3);
}

TEST(t_acceleration_test, add) {
    auto acc_1 = Acceleration<float>(5.0);
    auto acc_2 = Acceleration<float>(10.0);
    EXPECT_FLOAT_EQ((acc_1 + acc_2).mps2(), 15.0f);
}

TEST(t_acceleration_test, sub) {
    auto acc_1 = Acceleration<float>(15.0);
    auto acc_2 = Acceleration<float>(10.0);
    EXPECT_FLOAT_EQ((acc_1 - acc_2).mps2(), 5.0f);
}

TEST(t_acceleration_test, scalar_mul_div) {
    auto acc_1 = Acceleration<float>(6.0);
    auto acc_2 = 2 * acc_1 * 2;
    EXPECT_FLOAT_EQ(acc_2.mps2(), 24);
    auto acc_3 = acc_1 / 2;
    EXPECT_FLOAT_EQ(acc_3.mps2(), 3);
}

TEST(t_acceleration_test, mul) {
    auto time_1 = Time<float>(5.0);
    auto acc_1 = Acceleration<float>(20.0);
    auto speed_1 = acc_1 * time_1;
    EXPECT_FLOAT_EQ(speed_1.mps(), 100.0f);
}

TEST(t_acceleration_test, div) {
    auto speed_1 = Velocity<float>(12.0);
    auto time_1 = Time<float>(3.0);
    auto acc_1 = speed_1 / time_1;
    EXPECT_FLOAT_EQ(acc_1.mps2(), 4.0f);
}

TEST(t_acceleration_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, 1, 0, 0, 0, 0, 0};
    EXPECT_EQ(Acceleration<float>::dim(), dim);
    EXPECT_EQ(Acceleration<float>::TimeDim(), -2);
    EXPECT_EQ(Acceleration<float>::LengthDim(), 1);
    EXPECT_EQ(Acceleration<float>::MassDim(), 0);
    EXPECT_EQ(Acceleration<float>::ElCurrDim(), 0);
    EXPECT_EQ(Acceleration<float>::TdTempDim(), 0);
    EXPECT_EQ(Acceleration<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Acceleration<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}