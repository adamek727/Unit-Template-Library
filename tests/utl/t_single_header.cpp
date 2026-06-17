/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

// This target is compiled with only single_include/ on its include path (it
// does not link utl::utl), so it exercises the amalgamated single header in
// isolation from the multi-header tree.

#include <gtest/gtest.h>
#include <type_traits>
#include <utl/utl.hpp>

using namespace utl;

TEST(t_single_header_test, core_arithmetic_maps_to_named_unit) {
    auto d = Velocity<float>(30.0f) * Time<float>(5.0f);
    static_assert(std::is_same_v<decltype(d), Length<float>>, "velocity * time = length");
    EXPECT_FLOAT_EQ(d.m(), 150.0f);
}

TEST(t_single_header_test, v3_features_present) {
    auto rho = Mass<double>(10.0) / Volume<double>(2.0);
    static_assert(std::is_same_v<decltype(rho), Density<double>>, "density mapper present");
    EXPECT_DOUBLE_EQ(rho.kgpm3(), 5.0);

    auto torque = Energy<double>(10.0) / Angle<double>(2.0);
    static_assert(std::is_same_v<decltype(torque), Torque<double>>, "angle dimension present");
    EXPECT_DOUBLE_EQ(torque.Nm(), 5.0);

    auto sum = Length<float>(1.0f) + Length<double>(2.0);
    static_assert(std::is_same_v<decltype(sum), Length<double>>, "mixed precision present");
    EXPECT_DOUBLE_EQ(sum.m(), 3.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
