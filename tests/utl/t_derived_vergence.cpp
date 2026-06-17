/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "utl/utl.hpp"

using namespace utl;

TEST(t_derived_vergence_test, init) {
    auto v = Vergence<double>(2.0);
    EXPECT_DOUBLE_EQ(v.dpt(), 2.0);
}

TEST(t_derived_vergence_test, from_focal_length) {
    auto v = Vergence<double>(Length<double>(0.5));
    EXPECT_DOUBLE_EQ(v.dpt(), 2.0);
}

TEST(t_derived_vergence_test, mapped_from_division) {
    auto v = Area<double>(6.0) / Volume<double>(2.0);
    static_assert(std::is_same_v<decltype(v), Vergence<double>>, "area / volume = vergence (1/m)");
    EXPECT_DOUBLE_EQ(v.dpt(), 3.0);
}

TEST(t_derived_vergence_test, dim) {
    auto dim = std::array<int8_t, 8>{0, -1, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(Vergence<double>::dim(), dim);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
