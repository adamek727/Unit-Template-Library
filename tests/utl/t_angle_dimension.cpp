/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_angle_dimension_test, angle_is_first_class_dimension) {
    static_assert(Angle<double>::AngleDim() == 1, "rad is angle^1");
    static_assert(SolidAngle<double>::AngleDim() == 2, "sr is angle^2");
    static_assert(Unit<double>::AngleDim() == 0, "dimensionless is angle^0");
}

TEST(t_angle_dimension_test, angle_times_angle_is_solid_angle) {
    auto sa = Angle<double>(2.0) * Angle<double>(3.0);
    static_assert(std::is_same_v<decltype(sa), SolidAngle<double>>, "rad * rad = sr");
    EXPECT_DOUBLE_EQ(sa.sr(), 6.0);
}

TEST(t_angle_dimension_test, sqrt_solid_angle_is_angle) {
    auto a = sqrt(SolidAngle<double>(9.0));
    static_assert(std::is_same_v<decltype(a), Angle<double>>, "sqrt(sr) = rad");
    EXPECT_DOUBLE_EQ(a.rad(), 3.0);
}

TEST(t_angle_dimension_test, torque_is_distinct_from_energy) {
    static_assert(!std::is_same_v<Torque<double>, Energy<double>>, "torque and energy are different types");
    auto torque = Energy<double>(10.0) / Angle<double>(2.0);
    static_assert(std::is_same_v<decltype(torque), Torque<double>>, "energy / angle = torque");
    EXPECT_DOUBLE_EQ(torque.Nm(), 5.0);
    auto energy = torque * Angle<double>(2.0);
    static_assert(std::is_same_v<decltype(energy), Energy<double>>, "torque * angle = energy");
    EXPECT_DOUBLE_EQ(energy.J(), 10.0);
}

TEST(t_angle_dimension_test, lum_intensity_times_solid_angle_is_luminous_flux) {
    auto lf = LuminousIntensity<double>(60.0) * SolidAngle<double>(2.0);
    static_assert(std::is_same_v<decltype(lf), LuminousFlux<double>>, "cd * sr = lm");
    EXPECT_DOUBLE_EQ(lf.lm(), 120.0);
}

TEST(t_angle_dimension_test, trig_takes_angle_returns_scalar) {
    EXPECT_DOUBLE_EQ(sin(Angle<double>(0.0)), 0.0);
    EXPECT_DOUBLE_EQ(cos(Angle<double>(0.0)), 1.0);
    EXPECT_NEAR(tan(Angle<double>(0.0)), 0.0, 1e-12);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
