/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

// Property-based tests: algebraic identities checked across many randomized
// values. They are cheap insurance against mapper and operator regressions —
// a broken cross-unit mapping or a sign slip shows up as a violated identity
// rather than waiting for a hand-written example to happen to cover it.

#include <algorithm>
#include <cmath>
#include <random>
#include <gtest/gtest.h>
#include "utl/utl.hpp"

using namespace utl;

namespace {

    // Iterations per identity. A fixed seed keeps failures reproducible; the
    // sequence is identical on every machine and every run.
    constexpr int ITERATIONS = 1000;
    constexpr std::uint64_t SEED = 0x9E3779B97F4A7C15ull;

    // Relative comparison: floating-point round-trips are exact only up to a
    // few ULP, so tolerate an error that scales with the operands' magnitude.
    void expect_close(double a, double b, double rel = 1e-9) {
        const double scale = std::max({1.0, std::abs(a), std::abs(b)});
        EXPECT_NEAR(a, b, rel * scale);
    }

    void expect_close_f(float a, float b, float rel = 1e-4f) {
        const float scale = std::max({1.0f, std::abs(a), std::abs(b)});
        EXPECT_NEAR(a, b, rel * scale);
    }

} // namespace

// (a * b) / b == a, exercised through the cross-unit mapper:
// Velocity * Time -> Length, then Length / Time -> Velocity.
TEST(t_property_test, multiply_then_divide_round_trips) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> any(-1000.0, 1000.0);
    std::uniform_real_distribution<double> nonzero(1.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double a = any(rng);
        const double b = nonzero(rng);
        const auto v = Velocity<double>(a);
        const auto t = Time<double>(b);
        const auto back = (v * t) / t;
        expect_close(back.mps(), a);
    }
}

// (a + b) - b == a for a same-dimension chain that stays mapped to Length.
TEST(t_property_test, add_then_subtract_round_trips) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> any(-1000.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double a = any(rng);
        const double b = any(rng);
        const auto back = (Length<double>(a) + Length<double>(b)) - Length<double>(b);
        expect_close(back.m(), a);
    }
}

// inv(inv(x)) == x.
TEST(t_property_test, double_inverse_is_identity) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> nonzero(1.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double x = nonzero(rng);
        const auto roundtrip = Time<double>(x).inv().inv();
        expect_close(roundtrip.value(), x);
    }
}

// (a * k) / k == a for a scalar k, staying on the named-unit path.
TEST(t_property_test, scalar_multiply_then_divide_round_trips) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> any(-1000.0, 1000.0);
    std::uniform_real_distribution<double> nonzero(1.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double a = any(rng);
        const double k = nonzero(rng);
        const auto back = (Length<double>(a) * k) / k;
        expect_close(back.m(), a);
    }
}

// Cross-unit multiplication commutes: Velocity * Time == Time * Velocity,
// both mapping to Length.
TEST(t_property_test, cross_unit_multiplication_commutes) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> any(-1000.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double a = any(rng);
        const double b = any(rng);
        const auto lhs = Velocity<double>(a) * Time<double>(b);
        const auto rhs = Time<double>(b) * Velocity<double>(a);
        expect_close(lhs.m(), rhs.m());
    }
}

// sqrt(pow<2>(x)) == |x|: Length -> Area -> Length round trip through math.hpp.
TEST(t_property_test, sqrt_of_square_is_abs) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> any(-1000.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double x = any(rng);
        const auto area = pow<2>(Length<double>(x));
        const auto root = sqrt(area);
        expect_close(root.m(), std::abs(x));
    }
}

// Mass * Acceleration -> Force, then Force / Acceleration -> Mass.
TEST(t_property_test, force_factorisation_round_trips) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<double> any(-1000.0, 1000.0);
    std::uniform_real_distribution<double> nonzero(1.0, 1000.0);
    for (int i = 0; i < ITERATIONS; ++i) {
        const double m = any(rng);
        const double acc = nonzero(rng);
        const auto force = Mass<double>(m) * Acceleration<double>(acc);
        const auto mass_back = force / Acceleration<double>(acc);
        expect_close(mass_back.kg(), m);
    }
}

// The same round trip must also hold for the float storage type, exercising
// the float instantiations of the mapper and operators.
TEST(t_property_test, float_multiply_then_divide_round_trips) {
    std::mt19937_64 rng(SEED);
    std::uniform_real_distribution<float> any(-1000.0f, 1000.0f);
    std::uniform_real_distribution<float> nonzero(1.0f, 1000.0f);
    for (int i = 0; i < ITERATIONS; ++i) {
        const float a = any(rng);
        const float b = nonzero(rng);
        const auto back = (Velocity<float>(a) * Time<float>(b)) / Time<float>(b);
        expect_close_f(back.mps(), a);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
