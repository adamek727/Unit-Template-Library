/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/dose_equivalent.hpp"

using namespace utl;

TEST(t_dose_equivalent, init) {

    auto dose_eq_1 = DoseEquivalent<float>(5.0);
    EXPECT_FLOAT_EQ(dose_eq_1.Sv(), 5.0f);

    auto dose_eq_2 = DoseEquivalent<float>(AbsorbedDose<float>(5), 1.5);
    EXPECT_FLOAT_EQ(dose_eq_2.Sv(), 7.5);
}

TEST(t_dose_equivalent, add) {
    auto dose_eq_1 = DoseEquivalent<float>(5.0);
    auto dose_eq_2 = DoseEquivalent<float>(10.0);
    EXPECT_FLOAT_EQ((dose_eq_1 + dose_eq_2).Sv(), 15.0f);
}

TEST(t_dose_equivalent, sub) {
    auto dose_eq_1 = DoseEquivalent<float>(15.0);
    auto dose_eq_2 = DoseEquivalent<float>(10.0);
    EXPECT_FLOAT_EQ((dose_eq_1 - dose_eq_2).Sv(), 5.0f);
}

TEST(t_dose_equivalent, scalar_mul_div) {
    auto dose_eq_1 = DoseEquivalent<float>(6.0);
    auto dose_eq_2 = dose_eq_1 * 2;
    EXPECT_FLOAT_EQ(dose_eq_2.Sv(), 12);
    auto dose_eq_3 = dose_eq_1 / 2;
    EXPECT_FLOAT_EQ(dose_eq_3.Sv(), 3);
}

TEST(t_dose_equivalent, dim) {
    auto dim = std::array<int8_t, 7>{-2, 2, 0, 0, 0, 0, 0};
    EXPECT_EQ(DoseEquivalent<float>::dim(), dim);
    EXPECT_EQ(DoseEquivalent<float>::TimeDim(), -2);
    EXPECT_EQ(DoseEquivalent<float>::LengthDim(), 2);
    EXPECT_EQ(DoseEquivalent<float>::MassDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::ElCurrDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::TdTempDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::AmOfSubDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}