/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/utl.hpp"
#include "utl/utl.hpp"

using namespace utl;

TEST(t_mass_test, init) {
    auto mass_1 = Mass<float>(5.0);
    EXPECT_FLOAT_EQ(mass_1.kg(), 5.0f);
    EXPECT_FLOAT_EQ(mass_1.tonne(), 0.005f);
    EXPECT_FLOAT_EQ(mass_1.g(), 5000.0f);
    EXPECT_FLOAT_EQ(mass_1.mg(), 5000000.0f);
    EXPECT_FLOAT_EQ(mass_1.ug(), 5000000000.0f);
}

TEST(t_mass_test, add) {
    auto mass_1 = Mass<float>(5.0);
    auto mass_2 = Mass<float>(10.0);
    EXPECT_FLOAT_EQ((mass_1 + mass_2).kg(), 15);
}

TEST(t_mass_test, sub) {
    auto mass_1 = Mass<float>(15.0);
    auto mass_2 = Mass<float>(10.0);
    EXPECT_FLOAT_EQ((mass_1 - mass_2).kg(), 5);
}

TEST(t_mass_test, scalar_mul_div) {
    auto mass_1 = Mass<float>(6.0);
    auto mass_2 = 2 * mass_1 * 2;
    EXPECT_FLOAT_EQ(mass_2.kg(), 24);
    auto mass_3 = mass_1 / 2;
    EXPECT_FLOAT_EQ(mass_3.kg(), 3);
}

TEST(t_mass_test, inv) {
    auto mass_1 = Mass<float>(6.0);
    auto inv_mass = mass_1.inv();
    EXPECT_FLOAT_EQ(inv_mass.value(), 1.0f / 6.0f);
}

TEST(t_mass_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 1, 0, 0, 0, 0};
    EXPECT_EQ(Mass<float>::dim(), dim);
    EXPECT_EQ(Mass<float>::TimeDim(), 0);
    EXPECT_EQ(Mass<float>::LengthDim(), 0);
    EXPECT_EQ(Mass<float>::MassDim(), 1);
    EXPECT_EQ(Mass<float>::ElCurrDim(), 0);
    EXPECT_EQ(Mass<float>::TdTempDim(), 0);
    EXPECT_EQ(Mass<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Mass<float>::LumIntDim(), 0);
}

TEST(t_mass_test, mass_times_acceleration_is_force) {
    auto mass = Mass<float>(2.0);
    auto acceleration = Acceleration<float>(3.0);
    auto force = mass * acceleration;
    EXPECT_FLOAT_EQ(force.N(), 6.0f);
}

TEST(t_mass_test, imperial_conversions) {
    auto one_kg = Mass<float>(1.0);
    EXPECT_FLOAT_EQ(one_kg.lb(), 2.2046226f);
    EXPECT_FLOAT_EQ(one_kg.oz(), 35.273962f);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}