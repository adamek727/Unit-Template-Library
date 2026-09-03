/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

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
    auto dim = std::array<int8_t, 8>{-2, 2, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(DoseEquivalent<float>::dim(), dim);
    EXPECT_EQ(DoseEquivalent<float>::TimeDim(), -2);
    EXPECT_EQ(DoseEquivalent<float>::LengthDim(), 2);
    EXPECT_EQ(DoseEquivalent<float>::MassDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::ElCurrDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::TdTempDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::AmOfSubDim(), 0);
    EXPECT_EQ(DoseEquivalent<float>::LumIntDim(), 0);
}

TEST(t_dose_equivalent, operator_set_keeps_type) {
    auto unit_1 = DoseEquivalent<float>(6.0);
    static_assert(std::is_same_v<decltype(unit_1 + unit_1), DoseEquivalent<float>>, "+ must keep the type");
    static_assert(std::is_same_v<decltype(unit_1 - unit_1), DoseEquivalent<float>>, "- must keep the type");
    static_assert(std::is_same_v<decltype(-unit_1), DoseEquivalent<float>>, "unary - must keep the type");
    static_assert(std::is_same_v<decltype(unit_1 * 2.0f), DoseEquivalent<float>>, "* scalar must keep the type");
    static_assert(std::is_same_v<decltype(2.0f * unit_1), DoseEquivalent<float>>, "scalar * must keep the type");
    static_assert(std::is_same_v<decltype(unit_1 / 2.0f), DoseEquivalent<float>>, "/ scalar must keep the type");
    EXPECT_FLOAT_EQ((-unit_1).Sv(), -6);
    unit_1 += DoseEquivalent<float>(1.0);
    unit_1 -= DoseEquivalent<float>(2.0);
    EXPECT_FLOAT_EQ(unit_1.Sv(), 5);
    EXPECT_TRUE(unit_1 < DoseEquivalent<float>(6.0));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}