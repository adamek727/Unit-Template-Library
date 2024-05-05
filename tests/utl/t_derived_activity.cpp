/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/activity.hpp"

using namespace utl;

TEST(t_activity_test, init) {
    auto activity_1 = Activity<float>(50000);
    EXPECT_FLOAT_EQ(activity_1.Bq(), 50000.0f);
}

TEST(t_activity_test, add) {
    auto activity_1 = Activity<float>(5.0);
    auto activity_2 = Activity<float>(10.0);
    EXPECT_FLOAT_EQ((activity_1 + activity_2).Bq(), 15);
}

TEST(t_activity_test, sub) {
    auto activity_1 = Activity<float>(15.0);
    auto activity_2 = Activity<float>(10.0);
    EXPECT_FLOAT_EQ((activity_1 - activity_2).Bq(), 5);
}

TEST(t_activity_test, scalar_mul_div) {
    auto activity_1 = Activity<float>(6.0);
    auto activity_2 = 2 * activity_1 * 2;
    EXPECT_FLOAT_EQ(activity_2.Bq(), 24);
    auto activity_3 = activity_1 / 2;
    EXPECT_FLOAT_EQ(activity_3.Bq(), 3);
}

TEST(t_activity_test, dim) {
    auto dim = std::array<int8_t, 7>{-1, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(Activity<float>::dim(), dim);
    EXPECT_EQ(Activity<float>::TimeDim(), -1);
    EXPECT_EQ(Activity<float>::LengthDim(), 0);
    EXPECT_EQ(Activity<float>::MassDim(), 0);
    EXPECT_EQ(Activity<float>::ElCurrDim(), 0);
    EXPECT_EQ(Activity<float>::TdTempDim(), 0);
    EXPECT_EQ(Activity<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Activity<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}