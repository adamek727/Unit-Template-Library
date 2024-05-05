/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/time.hpp"
#include "utl/derived/catalytic_activity.hpp"

using namespace utl;

TEST(t_area_test, init) {
    auto catal_act_1 = CatalyticActivity<float>(5.0);
    EXPECT_FLOAT_EQ(catal_act_1.katal(), 5.0f);

    auto catal_act_2 = CatalyticActivity<float>(AmountOfSubstance<float>(6), Time<float>(2));
    EXPECT_FLOAT_EQ(catal_act_2.katal(), 3.0f);
}

TEST(t_area_test, add) {
    auto catal_act_1 = CatalyticActivity<float>(5.0);
    auto catal_act_2 = CatalyticActivity<float>(10.0);
    EXPECT_FLOAT_EQ((catal_act_1 + catal_act_2).katal(), 15);
}

TEST(t_area_test, sub) {
    auto catal_act_1 = CatalyticActivity<float>(15.0);
    auto catal_act_2 = CatalyticActivity<float>(10.0);
    EXPECT_FLOAT_EQ((catal_act_1 - catal_act_2).katal(), 5);
}

TEST(t_area_test, scalar_mul_div) {
    auto catal_act_1 = CatalyticActivity<float>(6.0);
    auto catal_act_2 = 2 * catal_act_1 * 2;
    EXPECT_FLOAT_EQ(catal_act_2.katal(), 24);
    auto catal_act_3 = catal_act_1 / 2;
    EXPECT_FLOAT_EQ(catal_act_3.katal(), 3);
}

TEST(t_area_test, mul) {
    auto catal_act_1 = CatalyticActivity<float>(15.0);
    auto time_1 = Time<float>(10.0);
    auto amout_of_substance_1 = catal_act_1 * time_1;
    EXPECT_FLOAT_EQ(amout_of_substance_1.mol(), 150);
}

TEST(t_area_test, div) {
    auto catal_act_1 = CatalyticActivity<float>(60.0);
    auto amout_of_substance_1 = AmountOfSubstance<float>(15.0);
    auto freq_1 = catal_act_1 / amout_of_substance_1;
    EXPECT_FLOAT_EQ(freq_1.Hz(), 4.0f);
    EXPECT_FLOAT_EQ(freq_1.inv().type().s(), 0.25f);
}

TEST(t_area_test, dim) {
    auto dim = std::array<int8_t, 7>{-1, 0, 0, 0, 0, 1, 0};
    EXPECT_EQ(CatalyticActivity<float>::dim(), dim);
    EXPECT_EQ(CatalyticActivity<float>::TimeDim(), -1);
    EXPECT_EQ(CatalyticActivity<float>::LengthDim(), 0);
    EXPECT_EQ(CatalyticActivity<float>::MassDim(), 0);
    EXPECT_EQ(CatalyticActivity<float>::ElCurrDim(), 0);
    EXPECT_EQ(CatalyticActivity<float>::TdTempDim(), 0);
    EXPECT_EQ(CatalyticActivity<float>::AmOfSubDim(), 1);
    EXPECT_EQ(CatalyticActivity<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}