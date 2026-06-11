/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_operators_test, velocity_times_time_is_length) {
    auto d = Velocity<float>(30) * Time<float>(5);
    EXPECT_FLOAT_EQ(d.m(), 150.0f);
}

TEST(t_operators_test, length_over_time_is_velocity) {
    auto v = Length<float>(100) / Time<float>(4);
    EXPECT_FLOAT_EQ(v.mps(), 25.0f);
}

TEST(t_operators_test, mass_times_acceleration_is_force) {
    auto f = Mass<float>(2) * Acceleration<float>(3);
    EXPECT_FLOAT_EQ(f.N(), 6.0f);
}

TEST(t_operators_test, length_squared_is_area_cubed_is_volume) {
    auto l = Length<float>(2);
    auto a = l * l;
    EXPECT_FLOAT_EQ(a.m2(), 4.0f);
    auto vol = a * l;
    EXPECT_FLOAT_EQ(vol.m3(), 8.0f);
}

TEST(t_operators_test, chained_expression_maps_to_named_unit) {
    auto m = Mass<double>(1);
    auto &c = speed_of_light_d;
    auto e = m * c * c;
    EXPECT_DOUBLE_EQ(e.J(), SPEED_OF_LIGHT_IN_VACUUM_VALUE * SPEED_OF_LIGHT_IN_VACUUM_VALUE);
}

TEST(t_operators_test, scalar_operations_preserve_named_unit) {
    auto g = Acceleration<float>(9.81f);
    auto tt = Time<float>(10);
    auto s = 0.5f * g * tt * tt;
    EXPECT_FLOAT_EQ(s.m(), 490.5f);
}

TEST(t_operators_test, same_dimension_add_sub_return_named_unit) {
    auto l = Length<float>(5) + Length<float>(10) - Length<float>(3);
    EXPECT_FLOAT_EQ(l.m(), 12.0f);
}

TEST(t_operators_test, unmapped_dimensions_fall_back_to_base_unit) {
    auto unnamed = Mass<float>(2) * Velocity<float>(3);
    EXPECT_FLOAT_EQ(unnamed.value(), 6.0f);
    EXPECT_EQ(unnamed.MassDim(), 1);
    EXPECT_EQ(unnamed.LengthDim(), 1);
    EXPECT_EQ(unnamed.TimeDim(), -1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
