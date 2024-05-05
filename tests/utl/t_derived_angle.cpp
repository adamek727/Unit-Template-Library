/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/angle.hpp"

using namespace utl;

TEST(t_derived_angle_test, init) {
    auto angle_1 = Angle<float>(M_PI / 2);
    EXPECT_FLOAT_EQ(angle_1.rad(), M_PI / 2);
    EXPECT_FLOAT_EQ(angle_1.deg(), 90);

    auto angle_2 = Angle<float>(-270, Angle<float>::TYPE::DEG);
    EXPECT_FLOAT_EQ(angle_2.rad(), -3 * M_PI / 2);
    EXPECT_FLOAT_EQ(angle_2.deg(), -270);
}

TEST(t_derived_angle_test, add) {
    auto angle_1 = Angle<float>(5.0);
    auto angle_2 = Angle<float>(10.0);
    EXPECT_FLOAT_EQ((angle_1 + angle_2).rad(), 15);
}

TEST(t_derived_angle_test, scalar_mul_div) {
    auto angle_1 = Angle<float>(6.0);
    auto angle_2 = 2 * angle_1 * 2;
    EXPECT_FLOAT_EQ(angle_2.rad(), 24);
    auto angle_3 = angle_1 / 2;
    EXPECT_FLOAT_EQ(angle_3.rad(), 3);
}

TEST(t_derived_angle_test, sub) {
    auto angle_1 = Angle<float>(15.0);
    auto angle_2 = Angle<float>(10.0);
    EXPECT_FLOAT_EQ((angle_1 - angle_2).rad(), 5);
}

TEST(t_derived_angle_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(Angle<float>::dim(), dim);
    EXPECT_EQ(Angle<float>::TimeDim(), 0);
    EXPECT_EQ(Angle<float>::LengthDim(), 0);
    EXPECT_EQ(Angle<float>::MassDim(), 0);
    EXPECT_EQ(Angle<float>::ElCurrDim(), 0);
    EXPECT_EQ(Angle<float>::TdTempDim(), 0);
    EXPECT_EQ(Angle<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Angle<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}