/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include <sstream>
#include "utl/utl.hpp"
#include "utl/io.hpp"

using namespace utl;

TEST(t_ux_test, comparisons) {
    auto short_length = Length<float>(5);
    auto long_length = Length<float>(10);
    EXPECT_TRUE(short_length < long_length);
    EXPECT_TRUE(short_length <= long_length);
    EXPECT_TRUE(long_length > short_length);
    EXPECT_TRUE(long_length >= short_length);
    EXPECT_TRUE(short_length != long_length);
    EXPECT_TRUE(short_length == Length<float>(5));
    EXPECT_FALSE(short_length == long_length);
}

TEST(t_ux_test, compound_assignment) {
    auto l = Length<float>(10);
    l += Length<float>(5);
    EXPECT_FLOAT_EQ(l.m(), 15);
    l -= Length<float>(3);
    EXPECT_FLOAT_EQ(l.m(), 12);
    l *= 2;
    EXPECT_FLOAT_EQ(l.m(), 24);
    l /= 4;
    EXPECT_FLOAT_EQ(l.m(), 6);
}

TEST(t_ux_test, unary_minus) {
    auto l = -Length<float>(5);
    EXPECT_FLOAT_EQ(l.m(), -5);
}

TEST(t_ux_test, literals) {
    using namespace utl::literals;
    EXPECT_DOUBLE_EQ((5.0_km).m(), 5000.0);
    EXPECT_DOUBLE_EQ((3_m).m(), 3.0);
    EXPECT_DOUBLE_EQ((1500.0_mm).m(), 1.5);
    EXPECT_DOUBLE_EQ((2.0_h).s(), 7200.0);
    EXPECT_DOUBLE_EQ((90.0_min).s(), 5400.0);
    EXPECT_DOUBLE_EQ((1.5_s).s(), 1.5);
    EXPECT_DOUBLE_EQ((500.0_ms).s(), 0.5);
    EXPECT_DOUBLE_EQ((2.0_kg).kg(), 2.0);
    EXPECT_DOUBLE_EQ((500.0_g).kg(), 0.5);
    EXPECT_DOUBLE_EQ((10.0_A).A(), 10.0);
    EXPECT_DOUBLE_EQ((300.0_K).K(), 300.0);
    EXPECT_DOUBLE_EQ((2.0_mol).mol(), 2.0);
    EXPECT_DOUBLE_EQ((7.0_cd).cd(), 7.0);
    EXPECT_DOUBLE_EQ((20.0_mps).mps(), 20.0);
    EXPECT_DOUBLE_EQ((36.0_kmph).mps(), 10.0);
    EXPECT_DOUBLE_EQ((9.0_N).N(), 9.0);
    EXPECT_DOUBLE_EQ((4.0_J).J(), 4.0);
    EXPECT_DOUBLE_EQ((100.0_W).W(), 100.0);
    EXPECT_DOUBLE_EQ((50.0_Hz).Hz(), 50.0);
    EXPECT_DOUBLE_EQ((1.0_Pa).Pa(), 1.0);
    EXPECT_DOUBLE_EQ((230.0_V).V(), 230.0);
}

TEST(t_ux_test, literals_compose_with_operators) {
    using namespace utl::literals;
    auto distance = 120.0_km + 500.0_m;
    EXPECT_DOUBLE_EQ(distance.m(), 120500.0);
    auto velocity = 100.0_m / 4.0_s;
    EXPECT_DOUBLE_EQ(velocity.mps(), 25.0);
}

TEST(t_ux_test, stream_output) {
    std::stringstream ss;
    ss << Length<float>(150);
    EXPECT_EQ(ss.str(), "150 [m]");

    ss.str("");
    ss << Velocity<float>(30);
    EXPECT_EQ(ss.str(), "30 [s^-1 m]");

    ss.str("");
    ss << Unit<float>(2);
    EXPECT_EQ(ss.str(), "2 [-]");
}

static_assert(!std::is_default_constructible_v<Length<double>>, "a named unit is never undefined");
static_assert(!std::is_convertible_v<double, Length<double>>, "a scalar never becomes a unit implicitly");

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
