/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/utl.hpp"

using namespace utl;
using namespace utl::literals;

constexpr auto track = Length<double>(1500.0);
static_assert(track.m() == 1500.0);
static_assert(track.km() == 1.5);

static_assert((track + track).m() == 3000.0);
static_assert((track - Length<double>(500.0)).m() == 1000.0);
static_assert((track * 2.0).m() == 3000.0);
static_assert((2.0 * track).m() == 3000.0);
static_assert((-track).m() == -1500.0);

static_assert((Velocity<double>(30) * Time<double>(5)).m() == 150.0);
static_assert((Length<double>(100) / Time<double>(4)).mps() == 25.0);

static_assert(120.0_km > 500.0_m);
static_assert((2.0_h).s() == 7200.0);
static_assert(50.0_kmph == Velocity<double>(50.0 / 3.6));

static_assert(speed_of_light_d.mps() == SPEED_OF_LIGHT_IN_VACUUM_VALUE);

constexpr auto rest_energy = Mass<double>(1) * speed_of_light_d * speed_of_light_d;
static_assert(rest_energy.J() == SPEED_OF_LIGHT_IN_VACUUM_VALUE * SPEED_OF_LIGHT_IN_VACUUM_VALUE);

constexpr auto room = ThermodynamicTemperature<double>(20.0, ThermodynamicTemperature<double>::TYPE::CELSIUS);
static_assert(room.K() == 293.15);

constexpr auto inverted = Time<double>(4).inv();
static_assert(inverted.value() == 0.25);

TEST(t_constexpr_test, compile_time_evaluation_proven_by_static_asserts) {
    SUCCEED();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
