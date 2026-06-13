/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/all.hpp"
#include "utl/derived/all.hpp"

#define UTL_DEFINE_LITERAL(suffix, UnitType, FACTOR)                               \
    constexpr auto operator"" suffix(long double value)->UnitType<double> {        \
        return UnitType<double>(static_cast<double>(value) * (FACTOR));            \
    }                                                                              \
    constexpr auto operator"" suffix(unsigned long long value)->UnitType<double> { \
        return UnitType<double>(static_cast<double>(value) * (FACTOR));            \
    }

namespace utl {
    namespace literals {

        UTL_DEFINE_LITERAL(_h, Time, SECS_IN_MINUTE *MINUTES_IN_HOUR)
        UTL_DEFINE_LITERAL(_min, Time, SECS_IN_MINUTE)
        UTL_DEFINE_LITERAL(_s, Time, 1.0)
        UTL_DEFINE_LITERAL(_ms, Time, MILLI)

        UTL_DEFINE_LITERAL(_km, Length, KILO)
        UTL_DEFINE_LITERAL(_m, Length, 1.0)
        UTL_DEFINE_LITERAL(_mm, Length, MILLI)

        UTL_DEFINE_LITERAL(_kg, Mass, 1.0)
        UTL_DEFINE_LITERAL(_g, Mass, MILLI)

        UTL_DEFINE_LITERAL(_A, ElectricCurrent, 1.0)
        UTL_DEFINE_LITERAL(_K, ThermodynamicTemperature, 1.0)
        UTL_DEFINE_LITERAL(_mol, AmountOfSubstance, 1.0)
        UTL_DEFINE_LITERAL(_cd, LuminousIntensity, 1.0)

        UTL_DEFINE_LITERAL(_mps, Velocity, 1.0)
        UTL_DEFINE_LITERAL(_kmph, Velocity, 1.0 / 3.6)

        UTL_DEFINE_LITERAL(_N, Force, 1.0)
        UTL_DEFINE_LITERAL(_J, Energy, 1.0)
        UTL_DEFINE_LITERAL(_W, Power, 1.0)
        UTL_DEFINE_LITERAL(_Hz, Frequency, 1.0)
        UTL_DEFINE_LITERAL(_Pa, Pressure, 1.0)
        UTL_DEFINE_LITERAL(_V, Voltage, 1.0)
        UTL_DEFINE_LITERAL(_rad, Angle, 1.0)
    } // namespace literals
} // namespace utl

#undef UTL_DEFINE_LITERAL
