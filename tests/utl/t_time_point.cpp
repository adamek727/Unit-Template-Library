/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include "utl/time_point.hpp"

using namespace utl;

TEST(t_time_point_test, duration_native_ns_accessors) {
    auto a = milliseconds(5);
    EXPECT_EQ(a.ns(), 5000000);
    EXPECT_EQ(a.us(), 5000);
    EXPECT_EQ(a.ms(), 5);
    EXPECT_EQ(seconds(2).s(), 2);
}

TEST(t_time_point_test, duration_arithmetic) {
    auto sum = milliseconds(5) + milliseconds(3);
    static_assert(std::is_same_v<decltype(sum), TimeDuration>, "duration + duration = duration");
    EXPECT_EQ(sum.ms(), 8);
    EXPECT_EQ((milliseconds(5) - milliseconds(2)).ms(), 3);
    EXPECT_EQ((milliseconds(5) * 2).ms(), 10);
    EXPECT_EQ((2 * milliseconds(5)).ms(), 10);
    EXPECT_EQ((-milliseconds(5)).ms(), -5);
}

TEST(t_time_point_test, stamp_minus_stamp_is_duration) {
    auto dt = TimeStamp(1500000000) - TimeStamp(1000000000);
    static_assert(std::is_same_v<decltype(dt), TimeDuration>, "stamp - stamp = duration");
    EXPECT_EQ(dt.ms(), 500);
}

TEST(t_time_point_test, stamp_plus_minus_duration_is_stamp) {
    auto t = TimeStamp(1000000000) + milliseconds(250);
    static_assert(std::is_same_v<decltype(t), TimeStamp>, "stamp + duration = stamp");
    EXPECT_EQ(t.ns(), 1250000000);
    EXPECT_EQ((TimeStamp(1000000000) - milliseconds(250)).ns(), 750000000);
}

TEST(t_time_point_test, bridge_to_dimensional_time) {
    auto t = milliseconds(1500).to_time();
    static_assert(std::is_same_v<decltype(t), Time<double>>, "to_time bridges to dimensional Time<double> seconds");
    EXPECT_DOUBLE_EQ(t.s(), 1.5);
}

TEST(t_time_point_test, comparisons) {
    EXPECT_TRUE(milliseconds(5) < milliseconds(6));
    EXPECT_TRUE(milliseconds(5) == milliseconds(5));
    EXPECT_TRUE(TimeStamp(100) < TimeStamp(200));
    EXPECT_TRUE(TimeStamp(200) >= TimeStamp(200));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
