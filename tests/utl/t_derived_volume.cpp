/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/volume.hpp"

using namespace utl;

TEST(t_volume_test, init) {
    auto volume_1 = Volume<float>(5.0);
    EXPECT_FLOAT_EQ(volume_1.m3(), 5.0f);
    EXPECT_FLOAT_EQ(volume_1.l(), 5000.0f);

    auto volume_2 = Volume<float>(Length<float>(5), Length<float>(10), Length<float>(20));
    EXPECT_FLOAT_EQ(volume_2.m3(), 1000.0f);

    auto volume_3 = Volume<float>(Area<float>(5), Length<float>(20));
    EXPECT_FLOAT_EQ(volume_3.m3(), 100.0f);
}

TEST(t_volume_test, add) {
    auto volume_1 = Volume<float>(5.0);
    auto volume_2 = Volume<float>(10.0);
    EXPECT_FLOAT_EQ((volume_1 + volume_2).m3(), 15.0);
}

TEST(t_volume_test, sub) {
    auto volume_1 = Volume<float>(15.0);
    auto volume_2 = Volume<float>(10.0);
    EXPECT_FLOAT_EQ((volume_1 - volume_2).m3(), 5.0);
}

TEST(t_derived_angle_test, scalar_mul_div) {
    auto volume_1 = Volume<float>(6.0);
    auto volume_2 = 2 * volume_1 * 2;
    EXPECT_FLOAT_EQ(volume_2.m3(), 24);
    auto volume_3 = volume_1 / 2;
    EXPECT_FLOAT_EQ(volume_3.m3(), 3);
}

TEST(t_volume_test, mul) {
    auto length_1 = Length<float>(15.0);
    auto length_2 = Length<float>(10.0);
    auto length_3 = Length<float>(5.0);

    auto volume_1 = length_1 * length_2 * length_3;
    EXPECT_FLOAT_EQ(volume_1.m3(), 750.0);

    auto area_1 = length_1 * length_2;
    auto volume_2 = area_1 * length_3;
    EXPECT_FLOAT_EQ(volume_2.m3(), 750.0);
}

TEST(t_volume_test, div) {
    auto volume_1 = Volume<float>(3000.0);
    auto area_1 = volume_1 / Length<float>(30.0);
    EXPECT_FLOAT_EQ(area_1.m2(), 100.0);

    auto length_1 = volume_1 / area_1;
    EXPECT_FLOAT_EQ(length_1.m(), 30.0);
}

TEST(t_volume_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 3, 0, 0, 0, 0, 0};
    EXPECT_EQ(Volume<float>::dim(), dim);
    EXPECT_EQ(Volume<float>::TimeDim(), 0);
    EXPECT_EQ(Volume<float>::LengthDim(), 3);
    EXPECT_EQ(Volume<float>::MassDim(), 0);
    EXPECT_EQ(Volume<float>::ElCurrDim(), 0);
    EXPECT_EQ(Volume<float>::TdTempDim(), 0);
    EXPECT_EQ(Volume<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Volume<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}