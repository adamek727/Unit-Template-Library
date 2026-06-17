/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_derived_concentration_test, init) {
    auto c = Concentration<double>(50.0);
    EXPECT_DOUBLE_EQ(c.molpm3(), 50.0);
}

TEST(t_derived_concentration_test, from_amount_and_volume) {
    auto c = Concentration<double>(AmountOfSubstance<double>(6.0), Volume<double>(2.0));
    EXPECT_DOUBLE_EQ(c.molpm3(), 3.0);
}

TEST(t_derived_concentration_test, mapped_from_division) {
    auto c = AmountOfSubstance<double>(10.0) / Volume<double>(4.0);
    static_assert(std::is_same_v<decltype(c), Concentration<double>>, "amount / volume = concentration");
    EXPECT_DOUBLE_EQ(c.molpm3(), 2.5);
}

TEST(t_derived_concentration_test, dim) {
    auto dim = std::array<int8_t, 8>{0, -3, 0, 0, 0, 1, 0, 0};
    EXPECT_EQ(Concentration<double>::dim(), dim);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
