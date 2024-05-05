/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/base/thermodynamic_temperature.hpp"

using namespace utl;

TEST(t_thermodynamic_temperature_test, init) {
    auto td_temp_1 = ThermodynamicTemperature<float>(5.0);
    EXPECT_FLOAT_EQ(td_temp_1.K(), 5.0f);
    EXPECT_FLOAT_EQ(td_temp_1.degC(), -268.15);
    EXPECT_FLOAT_EQ(td_temp_1.degF(), -450.67f);
}

TEST(t_thermodynamic_temperature_test, add) {
    auto td_temp_1 = ThermodynamicTemperature<float>(5.0);
    auto td_temp_2 = ThermodynamicTemperature<float>(10.0);
    EXPECT_FLOAT_EQ((td_temp_1 + td_temp_2).K(), 15);
}

TEST(t_thermodynamic_temperature_test, sub) {
    auto td_temp_1 = ThermodynamicTemperature<float>(15.0);
    auto td_temp_2 = ThermodynamicTemperature<float>(10.0);
    EXPECT_FLOAT_EQ((td_temp_1 - td_temp_2).K(), 5);
}

TEST(t_thermodynamic_temperature_test, scalar_mul_div) {
    auto td_temp_1 = ThermodynamicTemperature<float>(6.0);
    auto td_temp_2 = 2 * td_temp_1 * 2;
    EXPECT_FLOAT_EQ(td_temp_2.K(), 24);
    auto td_temp_3 = td_temp_1 / 2;
    EXPECT_FLOAT_EQ(td_temp_3.K(), 3);
}

TEST(t_thermodynamic_temperature_test, dim) {
    auto dim = std::array<int8_t, 7>{0, 0, 0, 0, 1, 0, 0};
    EXPECT_EQ(ThermodynamicTemperature<float>::dim(), dim);
    EXPECT_EQ(ThermodynamicTemperature<float>::TimeDim(), 0);
    EXPECT_EQ(ThermodynamicTemperature<float>::LengthDim(), 0);
    EXPECT_EQ(ThermodynamicTemperature<float>::MassDim(), 0);
    EXPECT_EQ(ThermodynamicTemperature<float>::ElCurrDim(), 0);
    EXPECT_EQ(ThermodynamicTemperature<float>::TdTempDim(), 1);
    EXPECT_EQ(ThermodynamicTemperature<float>::AmOfSubDim(), 0);
    EXPECT_EQ(ThermodynamicTemperature<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}