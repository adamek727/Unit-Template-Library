/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

// Fixture for the zero-overhead proof. Each `unit_*` function performs the
// same arithmetic as its `raw_*` twin but routed through the unit types. At
// -O2 the compiler must erase the wrapper entirely, so the two functions are
// expected to emit byte-for-byte identical machine code. tools/check_zero_overhead.py
// compiles this file to assembly and diffs each pair; this file is never
// linked, only assembled.
//
// extern "C" keeps the symbol names stable (raw_add / unit_add) so the checker
// can pair them without demangling.

#include "utl/utl.hpp"

using namespace utl;

extern "C" {

// --- addition: same-dimension operator+ ---

float raw_add(float a, float b) { return a + b; }
float unit_add(float a, float b) {
    return (Length<float>(a) + Length<float>(b)).m();
}

// --- subtraction: same-dimension operator- ---

float raw_sub(float a, float b) { return a - b; }
float unit_sub(float a, float b) {
    return (Length<float>(a) - Length<float>(b)).m();
}

// --- scalar multiply ---

float raw_scale(float a) { return a * 2.0f; }
float unit_scale(float a) {
    return (Length<float>(a) * 2.0f).m();
}

// --- unary negation ---

float raw_negate(float a) { return -a; }
float unit_negate(float a) {
    return (-Length<float>(a)).m();
}

// --- cross-unit multiply: Velocity * Time -> Length ---

float raw_mul(float a, float b) { return a * b; }
float unit_mul(float a, float b) {
    return (Velocity<float>(a) * Time<float>(b)).m();
}

// --- cross-unit divide: Length / Time -> Velocity ---

float raw_div(float a, float b) { return a / b; }
float unit_div(float a, float b) {
    return (Length<float>(a) / Time<float>(b)).mps();
}

// --- double storage, fused expression: 0.5 * g * t * t ---

double raw_fma(double g, double t) { return 0.5 * g * t * t; }
double unit_fma(double g, double t) {
    return (0.5 * Acceleration<double>(g) * Time<double>(t) * Time<double>(t)).m();
}

// --- reciprocal: Time::inv() ---

double raw_inv(double a) { return 1.0 / a; }
double unit_inv(double a) {
    return Time<double>(a).inv().value();
}

}  // extern "C"
