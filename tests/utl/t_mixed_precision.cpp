/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_mixed_precision_test, add_promotes_to_wider_type) {
    auto sum = Length<float>(1.0f) + Length<double>(2.0);
    static_assert(std::is_same_v<decltype(sum), Length<double>>, "mixed add must promote to the wider type");
    EXPECT_DOUBLE_EQ(sum.m(), 3.0);
}

TEST(t_mixed_precision_test, subtract_promotes_to_wider_type) {
    auto diff = Length<double>(5.0) - Length<float>(2.0f);
    static_assert(std::is_same_v<decltype(diff), Length<double>>, "mixed subtract must promote to the wider type");
    EXPECT_DOUBLE_EQ(diff.m(), 3.0);
}

TEST(t_mixed_precision_test, comparisons_across_precisions) {
    EXPECT_TRUE(Length<float>(1.0f) < Length<double>(2.0));
    EXPECT_TRUE(Length<double>(2.0) == Length<float>(2.0f));
    EXPECT_TRUE(Length<float>(3.0f) >= Length<double>(3.0));
    EXPECT_TRUE(Length<double>(4.0) != Length<float>(5.0f));
}

TEST(t_mixed_precision_test, cross_unit_multiply_promotes) {
    auto d = Velocity<float>(30.0f) * Time<double>(5.0);
    static_assert(std::is_same_v<decltype(d), Length<double>>, "mixed cross-unit multiply must promote");
    EXPECT_DOUBLE_EQ(d.m(), 150.0);
}

TEST(t_mixed_precision_test, cross_unit_divide_promotes) {
    auto v = Length<double>(100.0) / Time<float>(4.0f);
    static_assert(std::is_same_v<decltype(v), Velocity<double>>, "mixed cross-unit divide must promote");
    EXPECT_DOUBLE_EQ(v.mps(), 25.0);
}

TEST(t_mixed_precision_test, luminous_flux_add_promotes) {
    auto sum = LuminousFlux<float>(1.0f) + LuminousFlux<double>(2.0);
    static_assert(std::is_same_v<decltype(sum), LuminousFlux<double>>, "mixed LuminousFlux add must promote");
    EXPECT_DOUBLE_EQ(sum.lm(), 3.0);
}

TEST(t_mixed_precision_test, luminous_flux_divide_promotes) {
    auto intensity = LuminousFlux<double>(10.0) / SolidAngle<float>(2.0f);
    static_assert(std::is_same_v<decltype(intensity), LuminousIntensity<double>>, "mixed lm / sr must promote");
    EXPECT_DOUBLE_EQ(intensity.cd(), 5.0);
}

TEST(t_mixed_precision_test, illuminance_multiply_promotes) {
    auto flux = Illuminance<float>(3.0f) * Area<double>(2.0);
    static_assert(std::is_same_v<decltype(flux), LuminousFlux<double>>, "mixed lux * m2 must promote");
    EXPECT_DOUBLE_EQ(flux.lm(), 6.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
