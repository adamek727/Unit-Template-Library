/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <utility>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

using Temp = ThermodynamicTemperature<double>;
using Delta = TemperatureDelta<double>;

TEST(t_temperature_delta_test, temp_minus_temp_is_delta) {
    auto d = Temp(20, Temp::TYPE::CELSIUS) - Temp(5, Temp::TYPE::CELSIUS);
    static_assert(std::is_same_v<decltype(d), TemperatureDelta<double>>, "Temp - Temp must yield a TemperatureDelta");
    EXPECT_DOUBLE_EQ(d.K(), 15.0);
    EXPECT_DOUBLE_EQ(d.degC(), 15.0);
    EXPECT_DOUBLE_EQ(d.degF(), 27.0);
}

TEST(t_temperature_delta_test, temp_plus_delta_is_temp) {
    auto t = Temp(20, Temp::TYPE::CELSIUS) + Delta(5);
    static_assert(std::is_same_v<decltype(t), ThermodynamicTemperature<double>>, "Temp + Delta must yield a Temperature");
    EXPECT_DOUBLE_EQ(t.degC(), 25.0);
}

TEST(t_temperature_delta_test, delta_plus_temp_is_temp) {
    auto t = Delta(5) + Temp(20, Temp::TYPE::CELSIUS);
    static_assert(std::is_same_v<decltype(t), ThermodynamicTemperature<double>>, "Delta + Temp must yield a Temperature");
    EXPECT_DOUBLE_EQ(t.degC(), 25.0);
}

TEST(t_temperature_delta_test, temp_minus_delta_is_temp) {
    auto t = Temp(20, Temp::TYPE::CELSIUS) - Delta(5);
    static_assert(std::is_same_v<decltype(t), ThermodynamicTemperature<double>>, "Temp - Delta must yield a Temperature");
    EXPECT_DOUBLE_EQ(t.degC(), 15.0);
}

TEST(t_temperature_delta_test, delta_only_arithmetic) {
    auto d = Delta(10) + Delta(5) - Delta(3);
    static_assert(std::is_same_v<decltype(d), TemperatureDelta<double>>, "Delta +/- Delta must stay a TemperatureDelta");
    EXPECT_DOUBLE_EQ(d.K(), 12.0);
    EXPECT_DOUBLE_EQ((Delta(4) * 2.0).K(), 8.0);
    EXPECT_DOUBLE_EQ((2.0 * Delta(4)).K(), 8.0);
    EXPECT_DOUBLE_EQ((Delta(4) / 2.0).K(), 2.0);
    EXPECT_DOUBLE_EQ((-Delta(4)).K(), -4.0);
}

template<class Lhs, class Rhs, class = void>
struct can_add_assign : std::false_type {};

template<class Lhs, class Rhs>
struct can_add_assign<Lhs, Rhs, std::void_t<decltype(std::declval<Lhs &>() += std::declval<const Rhs &>())>> : std::true_type {};

template<class Lhs, class Rhs, class = void>
struct can_sub_assign : std::false_type {};

template<class Lhs, class Rhs>
struct can_sub_assign<Lhs, Rhs, std::void_t<decltype(std::declval<Lhs &>() -= std::declval<const Rhs &>())>> : std::true_type {};

TEST(t_temperature_delta_test, compound_assign_is_affine) {
    static_assert(can_add_assign<Temp, Delta>::value, "Temp += Delta must compile");
    static_assert(can_sub_assign<Temp, Delta>::value, "Temp -= Delta must compile");
    static_assert(!can_add_assign<Temp, Temp>::value, "Temp += Temp must not compile");
    static_assert(!can_sub_assign<Temp, Temp>::value, "Temp -= Temp must not compile");
    auto t = Temp(20, Temp::TYPE::CELSIUS);
    static_assert(std::is_same_v<decltype(t += Delta(1)), Temp &>, "Temp += Delta must return the temperature");
    t += Delta(5);
    EXPECT_DOUBLE_EQ(t.degC(), 25.0);
    t -= Delta(10);
    EXPECT_DOUBLE_EQ(t.degC(), 15.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
