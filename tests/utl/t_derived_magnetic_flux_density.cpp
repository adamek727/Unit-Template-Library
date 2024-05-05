/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/magnetic_flux_density.hpp"

using namespace utl;

TEST(t_magnetic_flux_dens_density_test, init) {
    auto magnetic_flux_dens_1 = MagneticFluxDensity<float>(5.0);
    EXPECT_FLOAT_EQ(magnetic_flux_dens_1.Tesla(), 5.0f);

    auto magnetic_flux_dens_2 = MagneticFluxDensity<float>(MagneticFlux<float>(6), Area<float>(2));
    EXPECT_FLOAT_EQ(magnetic_flux_dens_2.Tesla(), 3.0f);
}

TEST(t_magnetic_flux_dens_density_test, add) {
    auto magnetic_flux_dens_1 = MagneticFluxDensity<float>(5.0);
    auto magnetic_flux_dens_2 = MagneticFluxDensity<float>(10.0);
    EXPECT_FLOAT_EQ((magnetic_flux_dens_1 + magnetic_flux_dens_2).Tesla(), 15);
}

TEST(t_magnetic_flux_dens_density_test, sub) {
    auto magnetic_flux_dens_1 = MagneticFluxDensity<float>(15.0);
    auto magnetic_flux_dens_2 = MagneticFluxDensity<float>(10.0);
    EXPECT_FLOAT_EQ((magnetic_flux_dens_1 - magnetic_flux_dens_2).Tesla(), 5);
}

TEST(t_magnetic_flux_dens_density_test, scalar_mul_div) {
    auto magnetic_flux_dens_1 = MagneticFluxDensity<float>(6.0);
    auto magnetic_flux_dens_2 = 2 * magnetic_flux_dens_1 * 2;
    EXPECT_FLOAT_EQ(magnetic_flux_dens_2.Tesla(), 24);
    auto magnetic_flux_dens_3 = magnetic_flux_dens_1 / 2;
    EXPECT_FLOAT_EQ(magnetic_flux_dens_3.Tesla(), 3);
}

TEST(t_magnetic_flux_dens_density_test, mul) {
    auto magnetic_flux_dens_1 = MagneticFluxDensity<float>(6);
    auto area_1 = Area<float>(2);
    auto mag_flux_1 = magnetic_flux_dens_1 * area_1;
    EXPECT_FLOAT_EQ(mag_flux_1.Wb(), 12);
}

TEST(t_magnetic_flux_dens_density_test, dim) {
    auto dim = std::array<int8_t, 7>{-2, 0, 1, -1, 0, 0, 0};
    EXPECT_EQ(MagneticFluxDensity<float>::dim(), dim);
    EXPECT_EQ(MagneticFluxDensity<float>::TimeDim(), -2);
    EXPECT_EQ(MagneticFluxDensity<float>::LengthDim(), 0);
    EXPECT_EQ(MagneticFluxDensity<float>::MassDim(), 1);
    EXPECT_EQ(MagneticFluxDensity<float>::ElCurrDim(), -1);
    EXPECT_EQ(MagneticFluxDensity<float>::TdTempDim(), 0);
    EXPECT_EQ(MagneticFluxDensity<float>::AmOfSubDim(), 0);
    EXPECT_EQ(MagneticFluxDensity<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
