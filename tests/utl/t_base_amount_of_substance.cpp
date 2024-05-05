/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/amount_of_substance.hpp"

using namespace utl;

TEST(t_amount_of_substance_test, init) {
    auto am_of_sub_1 = AmountOfSubstance<float>(5.0);
    EXPECT_FLOAT_EQ(am_of_sub_1.mol(), 5.0f);
    EXPECT_FLOAT_EQ(am_of_sub_1.mmol(), 5000.0f);
    EXPECT_FLOAT_EQ(am_of_sub_1.umol(), 5000000.0f);
    EXPECT_FLOAT_EQ(am_of_sub_1.nmol(), 5000000000.0f);
}

TEST(t_amount_of_substance_test, add) {
    auto am_of_sub_1 = AmountOfSubstance<float>(5.0);
    auto am_of_sub_2 = AmountOfSubstance<float>(10.0);
    EXPECT_FLOAT_EQ((am_of_sub_1 + am_of_sub_2).mol(), 15);
}

TEST(t_amount_of_substance_test, sub) {
    auto am_of_sub_1 = AmountOfSubstance<float>(15.0);
    auto am_of_sub_2 = AmountOfSubstance<float>(10.0);
    EXPECT_FLOAT_EQ((am_of_sub_1 - am_of_sub_2).mol(), 5);
}

TEST(t_amount_of_substance_test, scalar_mul_div) {
    auto am_of_sub_1 = AmountOfSubstance<float>(6.0);
    auto am_of_sub_2 = 2 * am_of_sub_1 * 2;
    EXPECT_FLOAT_EQ(am_of_sub_2.mol(), 24);
    auto am_of_sub_3 = am_of_sub_1 / 2;
    EXPECT_FLOAT_EQ(am_of_sub_3.mol(), 3);
}

TEST(t_amount_of_substance_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 0, 0, 1, 0};
    EXPECT_EQ(AmountOfSubstance<float>::dim(), dim);
    EXPECT_EQ(AmountOfSubstance<float>::TimeDim(), 0);
    EXPECT_EQ(AmountOfSubstance<float>::LengthDim(), 0);
    EXPECT_EQ(AmountOfSubstance<float>::MassDim(), 0);
    EXPECT_EQ(AmountOfSubstance<float>::ElCurrDim(), 0);
    EXPECT_EQ(AmountOfSubstance<float>::TdTempDim(), 0);
    EXPECT_EQ(AmountOfSubstance<float>::AmOfSubDim(), 1);
    EXPECT_EQ(AmountOfSubstance<float>::LumIntDim(), 0);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}