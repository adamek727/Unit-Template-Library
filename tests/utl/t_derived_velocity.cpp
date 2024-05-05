/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/velocity.hpp"
#include "utl/derived/acceleration.hpp"

using namespace utl;

TEST(t_velocity_test, init) {
    auto velocity_1 = Velocity<float>(5.0);
    EXPECT_FLOAT_EQ(velocity_1.mps(), 5.0f);
    EXPECT_FLOAT_EQ(velocity_1.kmph(), 18.0f);

    auto velocity_2 = Velocity<float>(Length<float>(6), Time<float>(2));
    EXPECT_FLOAT_EQ(velocity_2.mps(), 3);
}

TEST(t_velocity_test, add) {
    auto velocity_1 = Velocity<float>(5.0);
    auto velocity_2 = Velocity<float>(10.0);
    EXPECT_FLOAT_EQ((velocity_1 + velocity_2).mps(), 15);
}

TEST(t_velocity_test, sub) {
    auto velocity_1 = Velocity<float>(15.0);
    auto velocity_2 = Velocity<float>(10.0);
    EXPECT_FLOAT_EQ((velocity_1 - velocity_2).mps(), 5);
}

TEST(t_derived_angle_test, scalar_mul_div) {
    auto velocity_1 = Velocity<float>(6.0);
    auto velocity_2 = 2 * velocity_1 * 2;
    EXPECT_FLOAT_EQ(velocity_2.mps(), 24);
    auto velocity_3 = velocity_1 / 2;
    EXPECT_FLOAT_EQ(velocity_3.mps(), 3);
}

TEST(t_velocity_test, mul) {
    auto velocity_1 = Velocity<float>(20);
    auto time_1 = Time<float>(5.0);
    auto length_1 = (velocity_1 * time_1);
    EXPECT_FLOAT_EQ(length_1.m(), 100.0);
}

TEST(t_velocity_test, div) {
    auto length_1 = Length<float>(15.0);
    auto time_1 = Time<float>(5.0);
    auto velocity_1 = length_1 / time_1;
    EXPECT_FLOAT_EQ(velocity_1.mps(), 3.0);

    auto acc_1 = velocity_1 / time_1;
    EXPECT_FLOAT_EQ(acc_1.mps2(), 3.0 / 5.0);

}

TEST(t_velocity_test, dim) {
    auto dim = std::array<int8_t, 7>{-1, 1, 0, 0, 0, 0, 0};
    EXPECT_EQ(Velocity<float>::dim(), dim);
    EXPECT_EQ(Velocity<float>::TimeDim(), -1);
    EXPECT_EQ(Velocity<float>::LengthDim(), 1);
    EXPECT_EQ(Velocity<float>::MassDim(), 0);
    EXPECT_EQ(Velocity<float>::ElCurrDim(), 0);
    EXPECT_EQ(Velocity<float>::TdTempDim(), 0);
    EXPECT_EQ(Velocity<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Velocity<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}