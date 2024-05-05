/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/area.hpp"

using namespace utl;

TEST(t_area_test, init) {
    auto area_1 = Area<float>(5.0);
    EXPECT_FLOAT_EQ(area_1.m2(), 5.0f);
    EXPECT_FLOAT_EQ(area_1.km2(), 0.000005f);
    EXPECT_FLOAT_EQ(area_1.mm2(), 5000000.0f);
    EXPECT_FLOAT_EQ(area_1.um2(), 5000000000000.0f);
    EXPECT_FLOAT_EQ(area_1.nm2(), 5000000000000000000.0f);

    EXPECT_FLOAT_EQ(area_1.ha(), 0.0005f);
    EXPECT_FLOAT_EQ(area_1.a(), 0.05f);

    auto area_2 = Area<float>(Length<float>(5), Length<float>(10));
    EXPECT_FLOAT_EQ(area_2.m2(), 50.0f);
}

TEST(t_area_test, add) {
    auto area_1 = Area<float>(5.0);
    auto area_2 = Area<float>(10.0);
    EXPECT_FLOAT_EQ((area_1 + area_2).m2(), 15);
}

TEST(t_area_test, sub) {
    auto area_1 = Area<float>(15.0);
    auto area_2 = Area<float>(10.0);
    EXPECT_FLOAT_EQ((area_1 - area_2).m2(), 5);
}

TEST(t_area_test, scalar_mul_div) {
    auto area_1 = Area<float>(6.0);
    auto area_2 = 2 * area_1 * 2;
    EXPECT_FLOAT_EQ(area_2.m2(), 24);
    auto area_3 = area_1 / 2;
    EXPECT_FLOAT_EQ(area_3.m2(), 3);
}

TEST(t_area_test, mul) {
    auto length_1 = Length<float>(15.0);
    auto length_2 = Length<float>(10.0);
    auto area_1 = length_1 * length_2;
    EXPECT_FLOAT_EQ(area_1.m2(), 150);
}

TEST(t_area_test, div) {
    auto area_1 = Area<float>(60.0);
    auto length_1 = Length<float>(15.0);
    auto length_2 = area_1 / length_1;
    EXPECT_FLOAT_EQ(length_2.m(), 4);
}

TEST(t_area_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 2, 0, 0, 0, 0, 0};
    EXPECT_EQ(Area<float>::dim(), dim);
    EXPECT_EQ(Area<float>::TimeDim(), 0);
    EXPECT_EQ(Area<float>::LengthDim(), 2);
    EXPECT_EQ(Area<float>::MassDim(), 0);
    EXPECT_EQ(Area<float>::ElCurrDim(), 0);
    EXPECT_EQ(Area<float>::TdTempDim(), 0);
    EXPECT_EQ(Area<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Area<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}