/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include <chrono>
#include "utl/chrono.hpp"

using namespace utl;

TEST(t_chrono_test, duration_from_chrono) {
    auto d = to_duration(std::chrono::milliseconds(250));
    EXPECT_EQ(d.ms(), 250);
    EXPECT_EQ(d.ns(), 250000000);
}

TEST(t_chrono_test, duration_to_chrono) {
    auto c = to_chrono(milliseconds(250));
    static_assert(std::is_same_v<decltype(c), std::chrono::nanoseconds>, "to_chrono(TimeDuration) yields nanoseconds");
    EXPECT_EQ(c.count(), 250000000);
}

TEST(t_chrono_test, timestamp_from_time_point) {
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> tp{std::chrono::seconds(5)};
    auto ts = to_timestamp(tp);
    EXPECT_EQ(ts.ns(), 5000000000);
}

TEST(t_chrono_test, timestamp_to_time_point) {
    auto tp = to_chrono<std::chrono::steady_clock>(TimeStamp(5000000000));
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
