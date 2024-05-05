/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/magnetic_flux.hpp"
#include "utl/derived/magnetic_flux_density.hpp"

using namespace utl;

TEST(t_magnetic_flux_test, init) {
    auto magnetic_flux_1 = MagneticFlux<float>(5.0);
    EXPECT_FLOAT_EQ(magnetic_flux_1.Wb(), 5.0f);

    auto magnetic_flux_2 = MagneticFlux<float>(Voltage<float>(6), Time<float>(2));
    EXPECT_FLOAT_EQ(magnetic_flux_2.Wb(), 12.0f);

    auto magnetic_flux_3 = MagneticFlux<float>(MagneticFluxDensity<float>(6), Area<float>(2));
    EXPECT_FLOAT_EQ(magnetic_flux_3.Wb(), 12.0f);
}

TEST(t_magnetic_flux_test, add) {
    auto magnetic_flux_1 = MagneticFlux<float>(5.0);
    auto magnetic_flux_2 = MagneticFlux<float>(10.0);
    EXPECT_FLOAT_EQ((magnetic_flux_1 + magnetic_flux_2).Wb(), 15);
}

TEST(t_magnetic_flux_test, sub) {
    auto magnetic_flux_1 = MagneticFlux<float>(15.0);
    auto magnetic_flux_2 = MagneticFlux<float>(10.0);
    EXPECT_FLOAT_EQ((magnetic_flux_1 - magnetic_flux_2).Wb(), 5);
}

TEST(t_magnetic_flux_test, scalar_mul_div) {
    auto magnetic_flux_1 = MagneticFlux<float>(6.0);
    auto magnetic_flux_2 = 2 * magnetic_flux_1 * 2;
    EXPECT_FLOAT_EQ(magnetic_flux_2.Wb(), 24);
    auto magnetic_flux_3 = magnetic_flux_1 / 2;
    EXPECT_FLOAT_EQ(magnetic_flux_3.Wb(), 3);
}

TEST(t_magnetic_flux_test, div) {
    auto magnetic_flux_dens_1 = MagneticFlux<float>(6);
    auto voltage_1 = Voltage<float>(2);
    auto time_1 = Time<float>(3);

    auto voltage_2 = magnetic_flux_dens_1 / time_1;
    EXPECT_FLOAT_EQ(voltage_2.V(), 2);

    auto time_2 = magnetic_flux_dens_1 / voltage_1;
    EXPECT_FLOAT_EQ(time_2.s(), 3);
}

TEST(t_magnetic_flux_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, 2, 1, -1, 0, 0, 0};
    EXPECT_EQ(MagneticFlux<float>::dim(), dim);
    EXPECT_EQ(MagneticFlux<float>::TimeDim(), -2);
    EXPECT_EQ(MagneticFlux<float>::LengthDim(), 2);
    EXPECT_EQ(MagneticFlux<float>::MassDim(), 1);
    EXPECT_EQ(MagneticFlux<float>::ElCurrDim(), -1);
    EXPECT_EQ(MagneticFlux<float>::TdTempDim(), 0);
    EXPECT_EQ(MagneticFlux<float>::AmOfSubDim(), 0);
    EXPECT_EQ(MagneticFlux<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
