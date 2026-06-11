/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/utl.hpp"

using namespace utl;

double speed_of_light_from_second_tu();

TEST(t_odr_test, header_included_in_two_translation_units_links) {
    EXPECT_DOUBLE_EQ(speed_of_light_d.mps(), SPEED_OF_LIGHT_IN_VACUUM_VALUE);
    EXPECT_DOUBLE_EQ(speed_of_light_from_second_tu(), SPEED_OF_LIGHT_IN_VACUUM_VALUE);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
