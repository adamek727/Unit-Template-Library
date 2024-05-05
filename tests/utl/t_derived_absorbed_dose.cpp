/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/absorbed_dose.hpp"

using namespace utl;

TEST(t_absorbed_dose, init) {

    auto abs_dose_1 = AbsorbedDose<float>(5.0);
    EXPECT_FLOAT_EQ(abs_dose_1.Gy(), 5.0f);

    auto abs_dose_2 = AbsorbedDose<float>(Energy<float>(6), Mass<float>(2));
    EXPECT_FLOAT_EQ(abs_dose_2.Gy(), 3);
}

TEST(t_absorbed_dose, add) {
    auto abs_dose_1 = AbsorbedDose<float>(5.0);
    auto abs_dose_2 = AbsorbedDose<float>(10.0);
    EXPECT_FLOAT_EQ((abs_dose_1 + abs_dose_2).Gy(), 15.0f);
}

TEST(t_absorbed_dose, sub) {
    auto abs_dose_1 = AbsorbedDose<float>(15.0);
    auto abs_dose_2 = AbsorbedDose<float>(10.0);
    EXPECT_FLOAT_EQ((abs_dose_1 - abs_dose_2).Gy(), 5.0f);
}

TEST(t_absorbed_dose, scalar_mul_div) {
    auto abs_dose_1 = AbsorbedDose<float>(6.0);
    auto abs_dose_2 = abs_dose_1 * 2;
    EXPECT_FLOAT_EQ(abs_dose_2.Gy(), 12);
    auto abs_dose_3 = abs_dose_1 / 2;
    EXPECT_FLOAT_EQ(abs_dose_3.Gy(), 3);
}

TEST(t_absorbed_dose, mul) {
    auto mass_1 = Mass<float>(5.0);
    auto abs_dose_1 = AbsorbedDose<float>(20.0);
    auto energy_1 = abs_dose_1 * mass_1;
    EXPECT_FLOAT_EQ(energy_1.J(), 100.0f);
}

TEST(t_absorbed_dose, dim) {
    auto dim = std::array<int8_t, 7>{-2, 2, 0, 0, 0, 0, 0};
    EXPECT_EQ(AbsorbedDose<float>::dim(), dim);
    EXPECT_EQ(AbsorbedDose<float>::TimeDim(), -2);
    EXPECT_EQ(AbsorbedDose<float>::LengthDim(), 2);
    EXPECT_EQ(AbsorbedDose<float>::MassDim(), 0);
    EXPECT_EQ(AbsorbedDose<float>::ElCurrDim(), 0);
    EXPECT_EQ(AbsorbedDose<float>::TdTempDim(), 0);
    EXPECT_EQ(AbsorbedDose<float>::AmOfSubDim(), 0);
    EXPECT_EQ(AbsorbedDose<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}