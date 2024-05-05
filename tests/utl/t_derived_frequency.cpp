/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#include <gtest/gtest.h>
#include "utl/derived/frequency.hpp"

using namespace utl;

TEST(t_frequency_test, init) {
    auto freq_1 = Frequency<float>(50000);
    EXPECT_FLOAT_EQ(freq_1.Hz(), 50000.0f);
    EXPECT_FLOAT_EQ(freq_1.kHz(), 50.0f);
    EXPECT_FLOAT_EQ(freq_1.MHz(), 0.05f);
    EXPECT_FLOAT_EQ(freq_1.GHz(), 0.00005f);
    EXPECT_FLOAT_EQ(freq_1.THz(), 0.00000005f);
}

TEST(t_frequency_test, add) {
    auto freq_1 = Frequency<float>(5.0);
    auto freq_2 = Frequency<float>(10.0);
    EXPECT_FLOAT_EQ((freq_1 + freq_2).Hz(), 15);
}

TEST(t_frequency_test, sub) {
    auto freq_1 = Frequency<float>(15.0);
    auto freq_2 = Frequency<float>(10.0);
    EXPECT_FLOAT_EQ((freq_1 - freq_2).Hz(), 5);
}

TEST(t_frequency_test, scalar_mul_div) {
    auto freq_1 = Frequency<float>(6.0);
    auto freq_2 = 2 * freq_1 * 2;
    EXPECT_FLOAT_EQ(freq_2.Hz(), 24);
    auto freq_3 = freq_1 / 2;
    EXPECT_FLOAT_EQ(freq_3.Hz(), 3);
}

TEST(t_frequency_test, inversion) {
    auto freq_1 = Frequency<float>(5.0);
    auto time_1 = freq_1.inv().type();
    EXPECT_FLOAT_EQ(time_1.s(), 0.2);
}

TEST(t_frequency_test, dim) {
    auto dim = std::array<int8_t, 7>{-1, 0, 0, 0, 0, 0, 0};
    EXPECT_EQ(Frequency<float>::dim(), dim);
    EXPECT_EQ(Frequency<float>::TimeDim(), -1);
    EXPECT_EQ(Frequency<float>::LengthDim(), 0);
    EXPECT_EQ(Frequency<float>::MassDim(), 0);
    EXPECT_EQ(Frequency<float>::ElCurrDim(), 0);
    EXPECT_EQ(Frequency<float>::TdTempDim(), 0);
    EXPECT_EQ(Frequency<float>::AmOfSubDim(), 0);
    EXPECT_EQ(Frequency<float>::LumIntDim(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}