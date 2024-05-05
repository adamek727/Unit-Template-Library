/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/solid_angle.hpp"

using namespace utl;

TEST(t_derived_angle_test, init) {
    auto solid_angle_1 = SolidAngle<float>(10);
    EXPECT_FLOAT_EQ(solid_angle_1.sr(), 10);

    auto solid_angle_2 = SolidAngle<float>(Area<float>(5), Area<float>(2));
    EXPECT_FLOAT_EQ(solid_angle_2.sr(), 2.5f);

    auto solid_angle_3 = SolidAngle<float>(Area<float>(27), Length<float>(3));
    EXPECT_FLOAT_EQ(solid_angle_3.sr(), 3);
}

TEST(t_derived_angle_test, add) {
    auto solid_angle_1 = SolidAngle<float>(5.0);
    auto solid_angle_2 = SolidAngle<float>(10.0);
    EXPECT_FLOAT_EQ((solid_angle_1 + solid_angle_2).sr(), 15);
}

TEST(t_derived_angle_test, sub) {
    auto solid_angle_1 = SolidAngle<float>(15.0);
    auto solid_angle_2 = SolidAngle<float>(10.0);
    EXPECT_FLOAT_EQ((solid_angle_1 - solid_angle_2).sr(), 5);
}

TEST(t_derived_angle_test, scalar_mul_div) {
    auto solid_angle_1 = SolidAngle<float>(6.0);
    auto solid_angle_2 = 2 * solid_angle_1 * 2;
    EXPECT_FLOAT_EQ(solid_angle_2.sr(), 24);
    auto solid_angle_3 = solid_angle_1 / 2;
    EXPECT_FLOAT_EQ(solid_angle_3.sr(), 3);
}

TEST(t_derived_angle_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(SolidAngle<float>::dim(), dim);
    EXPECT_EQ(SolidAngle<float>::TimeDim(), 0);
    EXPECT_EQ(SolidAngle<float>::LengthDim(), 0);
    EXPECT_EQ(SolidAngle<float>::MassDim(), 0);
    EXPECT_EQ(SolidAngle<float>::ElCurrDim(), 0);
    EXPECT_EQ(SolidAngle<float>::TdTempDim(), 0);
    EXPECT_EQ(SolidAngle<float>::AmOfSubDim(), 0);
    EXPECT_EQ(SolidAngle<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}