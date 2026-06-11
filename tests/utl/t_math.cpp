/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_math_test, sqrt_halves_dimensions) {
    auto side = sqrt(Area<float>(25));
    EXPECT_FLOAT_EQ(side.m(), 5.0f);

    auto duration = sqrt(Length<float>(20) / Acceleration<float>(5));
    EXPECT_FLOAT_EQ(duration.s(), 2.0f);
}

TEST(t_math_test, pow_multiplies_dimensions) {
    auto area = pow<2>(Length<float>(3));
    EXPECT_FLOAT_EQ(area.m2(), 9.0f);

    auto volume = pow<3>(Length<float>(2));
    EXPECT_FLOAT_EQ(volume.m3(), 8.0f);

    auto scalar = pow<0>(Length<float>(7));
    EXPECT_FLOAT_EQ(scalar.value(), 1.0f);
}

TEST(t_math_test, abs_preserves_unit) {
    EXPECT_FLOAT_EQ(abs(Length<float>(-5)).m(), 5.0f);
    EXPECT_FLOAT_EQ(abs(Length<float>(5)).m(), 5.0f);
}

TEST(t_math_test, min_max) {
    auto slow = Velocity<float>(10);
    auto fast = Velocity<float>(20);
    EXPECT_FLOAT_EQ(min(slow, fast).mps(), 10.0f);
    EXPECT_FLOAT_EQ(max(slow, fast).mps(), 20.0f);
}

TEST(t_math_test, compile_time_helpers) {
    static_assert(pow<2>(Length<double>(3)).m2() == 9.0);
    static_assert(abs(Length<double>(-5)).m() == 5.0);
    static_assert(min(Time<double>(1), Time<double>(2)).s() == 1.0);
    static_assert(max(Time<double>(1), Time<double>(2)).s() == 2.0);
    SUCCEED();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
