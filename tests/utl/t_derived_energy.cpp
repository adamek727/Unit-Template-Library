/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/energy.hpp"

using namespace utl;

TEST(t_energy_test, init) {
    auto energy_1 = Energy<float>(10000);
    EXPECT_FLOAT_EQ(energy_1.J(), 10000.0f);
    EXPECT_FLOAT_EQ(energy_1.kJ(), 10.0f);
    EXPECT_FLOAT_EQ(energy_1.mJ(), 10000000.0f);
    EXPECT_FLOAT_EQ(energy_1.kWh(), 0.0027777778f);
    EXPECT_FLOAT_EQ(energy_1.eV(), 6.241509343260179e+22);

    auto energy_2 = Energy<float>(Force<float>(5), Length<float>(2));
    EXPECT_FLOAT_EQ(energy_2.J(), 10.0f);
}

TEST(t_energy_test, add) {
    auto energy_1 = Energy<float>(5.0);
    auto energy_2 = Energy<float>(10.0);
    EXPECT_FLOAT_EQ((energy_1 + energy_2).J(), 15);
}

TEST(t_energy_test, sub) {
    auto energy_1 = Energy<float>(15.0);
    auto energy_2 = Energy<float>(10.0);
    EXPECT_FLOAT_EQ((energy_1 - energy_2).J(), 5);
}

TEST(t_energy_test, scalar_mul_div) {
    auto energy_1 = Energy<float>(6.0);
    auto energy_2 = 2 * energy_1 * 2;
    EXPECT_FLOAT_EQ(energy_2.J(), 24);
    auto energy_3 = energy_1 / 2;
    EXPECT_FLOAT_EQ(energy_3.J(), 3);
}

TEST(t_energy_test, div) {
    auto energy_1 = Energy<float>(6.0);
    auto length_1 = Length<float>(2.0);
    auto force_1 = energy_1 / length_1;
    EXPECT_FLOAT_EQ(force_1.N(), 3);
}

TEST(t_energy_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, 2, 1, 0, 0, 0, 0};
    EXPECT_EQ(Energy<float>::dim(), dim);
    EXPECT_EQ(Energy<float>::TimeDim(), -2);
    EXPECT_EQ(Energy<float>::LengthDim(), 2);
    EXPECT_EQ(Energy<float>::MassDim(), 1);
    EXPECT_EQ(Energy<float>::ElCurrDim(), 0);
    EXPECT_EQ(Energy<float>::TdTempDim(), 0);
    EXPECT_EQ(Energy<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Energy<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}