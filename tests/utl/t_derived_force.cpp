/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/force.hpp"
#include "utl/derived/area.hpp"
#include "utl/derived/pressure.hpp"
#include "utl/derived/energy.hpp"

using namespace utl;

TEST(t_force_test, init) {
    auto force_1 = Force<float>(50000);
    EXPECT_FLOAT_EQ(force_1.N(), 50000.0f);
}

TEST(t_force_test, add) {
    auto force_1 = Force<float>(5.0);
    auto force_2 = Force<float>(10.0);
    EXPECT_FLOAT_EQ((force_1 + force_2).N(), 15);
}

TEST(t_force_test, sub) {
    auto force_1 = Force<float>(15.0);
    auto force_2 = Force<float>(10.0);
    EXPECT_FLOAT_EQ((force_1 - force_2).N(), 5);
}

TEST(t_force_test, scalar_mul_div) {
    auto force_1 = Force<float>(6.0);
    auto force_2 = 2 * force_1 * 2;
    EXPECT_FLOAT_EQ(force_2.N(), 24);
    auto force_3 = force_1 / 2;
    EXPECT_FLOAT_EQ(force_3.N(), 3);
}

TEST(t_force_test, mul) {
    auto force_1 = Force<float>(6.0);
    auto length_1 = Length<float>(2.0);
    auto energy_1 = force_1 * length_1;
    EXPECT_FLOAT_EQ(energy_1.J(), 12);
}

TEST(t_force_test, div) {
    auto force_1 = Force<float>(6.0);
    auto mass_1 = Mass<float>(3.0);
    auto acc_1 = Acceleration<float>(2.0);
    auto area_1 = Area<float>(1.5f);

    auto acc_2 = force_1 / mass_1;
    EXPECT_FLOAT_EQ(acc_2.mps2(), 2);

    auto mass_2 = force_1 / acc_1;
    EXPECT_FLOAT_EQ(mass_2.kg(), 3);

    auto pressure_1 = force_1 / area_1;
    EXPECT_FLOAT_EQ(pressure_1.Pa(), 4);
}

TEST(t_force_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, 1, 1, 0, 0, 0, 0};
    EXPECT_EQ(Force<float>::dim(), dim);
    EXPECT_EQ(Force<float>::TimeDim(), -2);
    EXPECT_EQ(Force<float>::LengthDim(), 1);
    EXPECT_EQ(Force<float>::MassDim(), 1);
    EXPECT_EQ(Force<float>::ElCurrDim(), 0);
    EXPECT_EQ(Force<float>::TdTempDim(), 0);
    EXPECT_EQ(Force<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Force<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}