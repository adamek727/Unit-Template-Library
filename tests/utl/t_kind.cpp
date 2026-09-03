/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_kind_test, math_helpers_keep_the_kind) {
    auto a = Activity<double>(-3.0);
    static_assert(std::is_same_v<decltype(abs(a)), Activity<double>>, "abs must keep Activity");
    static_assert(std::is_same_v<decltype(min(a, a)), Activity<double>>, "min must keep Activity");
    static_assert(std::is_same_v<decltype(max(a, a)), Activity<double>>, "max must keep Activity");
    static_assert(std::is_same_v<decltype(abs(DoseEquivalent<double>(1.0))), DoseEquivalent<double>>, "abs must keep DoseEquivalent");
    static_assert(std::is_same_v<decltype(abs(TemperatureDelta<double>(1.0))), TemperatureDelta<double>>, "abs must keep TemperatureDelta");
    EXPECT_DOUBLE_EQ(abs(a).Bq(), 3.0);
}

TEST(t_kind_test, mixed_precision_promotes_within_a_kind) {
    auto a = Activity<float>(1.0f) + Activity<double>(2.0);
    static_assert(std::is_same_v<decltype(a), Activity<double>>, "mixed Activity add must promote");
    EXPECT_DOUBLE_EQ(a.Bq(), 3.0);
    auto d = TemperatureDelta<float>(1.0f) - TemperatureDelta<double>(3.0);
    static_assert(std::is_same_v<decltype(d), TemperatureDelta<double>>, "mixed delta subtract must promote");
    EXPECT_DOUBLE_EQ(d.K(), -2.0);
    EXPECT_TRUE(DoseEquivalent<float>(1.0f) < DoseEquivalent<double>(2.0));
}

TEST(t_kind_test, unary_minus_and_scalars_keep_the_kind) {
    auto d = TemperatureDelta<double>(4.0);
    static_assert(std::is_same_v<decltype(-d), TemperatureDelta<double>>, "unary minus must keep the kind");
    static_assert(std::is_same_v<decltype(2.0 * d), TemperatureDelta<double>>, "scalar * must keep the kind");
    static_assert(std::is_same_v<decltype(d / 2.0), TemperatureDelta<double>>, "/ scalar must keep the kind");
    EXPECT_DOUBLE_EQ((-d).K(), -4.0);
}

TEST(t_kind_test, dimension_changing_operations_drop_the_kind) {
    auto decays = Activity<double>(5.0) * Time<double>(2.0);
    static_assert(std::is_same_v<decltype(decays), Unit<double>>, "Bq * s is a plain dimensionless count");
    EXPECT_DOUBLE_EQ(decays.value(), 10.0);
    static_assert(std::is_same_v<decltype(Activity<double>(4.0).inv()), TimeUnit<double>>, "1 / Bq is a plain 1/s");
    static_assert(std::is_same_v<decltype(sqrt(DoseEquivalent<double>(4.0))), Velocity<double>>, "sqrt(Sv) is a plain m/s");
    static_assert(std::is_same_v<decltype(Energy<double>(1.0) / TemperatureDelta<double>(1.0)), decltype(Energy<double>(1.0) / ThermodynamicTemperature<double>(1.0))>, "J / delta-K and J / K are the same quantity");
}

TEST(t_kind_test, temperature_affine_arithmetic_is_unchanged) {
    using Temp = ThermodynamicTemperature<double>;
    auto d = Temp(300.0) - Temp(280.0);
    static_assert(std::is_same_v<decltype(d), TemperatureDelta<double>>, "Temp - Temp must yield a delta");
    static_assert(std::is_same_v<decltype(Temp(1.0) + d), Temp>, "Temp + delta must yield a Temp");
    static_assert(std::is_same_v<decltype(d + Temp(1.0)), Temp>, "delta + Temp must yield a Temp");
    EXPECT_DOUBLE_EQ((Temp(280.0) + d).K(), 300.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
