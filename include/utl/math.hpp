/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <cmath>
#include <cstdint>
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    auto sqrt(const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &unit)
        -> mapped_unit_t<BaseUnit<T, TIME / 2, LENGTH / 2, MASS / 2, EL_CURR / 2, TD_TEMP / 2, AM_OF_SUB / 2, LUM_INT / 2>> {
        static_assert(TIME % 2 == 0 && LENGTH % 2 == 0 && MASS % 2 == 0 && EL_CURR % 2 == 0 && TD_TEMP % 2 == 0 && AM_OF_SUB % 2 == 0 && LUM_INT % 2 == 0,
                      "sqrt requires all dimension exponents to be even");
        using Result = mapped_unit_t<BaseUnit<T, TIME / 2, LENGTH / 2, MASS / 2, EL_CURR / 2, TD_TEMP / 2, AM_OF_SUB / 2, LUM_INT / 2>>;
        return Result(std::sqrt(unit.value()));
    }

    template<int8_t N, typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    constexpr auto pow(const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &unit)
        -> mapped_unit_t<BaseUnit<T, TIME * N, LENGTH * N, MASS * N, EL_CURR * N, TD_TEMP * N, AM_OF_SUB * N, LUM_INT * N>> {
        static_assert(N >= 0, "pow supports non-negative exponents; use inv() for reciprocals");
        using Result = mapped_unit_t<BaseUnit<T, TIME * N, LENGTH * N, MASS * N, EL_CURR * N, TD_TEMP * N, AM_OF_SUB * N, LUM_INT * N>>;
        T result = 1;
        for (int8_t i = 0; i < N; ++i) {
            result *= unit.value();
        }
        return Result(result);
    }

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    constexpr auto abs(const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &unit)
        -> mapped_unit_t<BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>> {
        using Result = mapped_unit_t<BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>>;
        return Result(unit.value() < 0 ? -unit.value() : unit.value());
    }

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    constexpr auto min(const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &lhs,
                       const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &rhs)
        -> mapped_unit_t<BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>> {
        using Result = mapped_unit_t<BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>>;
        return Result(lhs.value() < rhs.value() ? lhs.value() : rhs.value());
    }

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    constexpr auto max(const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &lhs,
                       const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &rhs)
        -> mapped_unit_t<BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>> {
        using Result = mapped_unit_t<BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>>;
        return Result(lhs.value() < rhs.value() ? rhs.value() : lhs.value());
    }
} // namespace utl
