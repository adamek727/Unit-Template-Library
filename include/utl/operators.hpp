/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <cstdint>
#include <type_traits>
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T_L, typename T_R,
             int8_t TIME_L, int8_t LENGTH_L, int8_t MASS_L, int8_t EL_CURR_L, int8_t TD_TEMP_L, int8_t AM_OF_SUB_L, int8_t LUM_INT_L, int8_t ANGLE_L,
             int8_t TIME_R, int8_t LENGTH_R, int8_t MASS_R, int8_t EL_CURR_R, int8_t TD_TEMP_R, int8_t AM_OF_SUB_R, int8_t LUM_INT_R, int8_t ANGLE_R>
    constexpr auto operator*(
        const BaseUnit<T_L, TIME_L, LENGTH_L, MASS_L, EL_CURR_L, TD_TEMP_L, AM_OF_SUB_L, LUM_INT_L, ANGLE_L> &lhs,
        const BaseUnit<T_R, TIME_R, LENGTH_R, MASS_R, EL_CURR_R, TD_TEMP_R, AM_OF_SUB_R, LUM_INT_R, ANGLE_R> &rhs)
        -> mapped_unit_t<BaseUnit<std::common_type_t<T_L, T_R>,
                                  TIME_L + TIME_R,
                                  LENGTH_L + LENGTH_R,
                                  MASS_L + MASS_R,
                                  EL_CURR_L + EL_CURR_R,
                                  TD_TEMP_L + TD_TEMP_R,
                                  AM_OF_SUB_L + AM_OF_SUB_R,
                                  LUM_INT_L + LUM_INT_R,
                                  ANGLE_L + ANGLE_R>> {
        using Result = mapped_unit_t<BaseUnit<std::common_type_t<T_L, T_R>,
                                              TIME_L + TIME_R,
                                              LENGTH_L + LENGTH_R,
                                              MASS_L + MASS_R,
                                              EL_CURR_L + EL_CURR_R,
                                              TD_TEMP_L + TD_TEMP_R,
                                              AM_OF_SUB_L + AM_OF_SUB_R,
                                              LUM_INT_L + LUM_INT_R,
                                              ANGLE_L + ANGLE_R>>;
        return Result(lhs.value() * rhs.value());
    }

    template<typename T_L, typename T_R,
             int8_t TIME_L, int8_t LENGTH_L, int8_t MASS_L, int8_t EL_CURR_L, int8_t TD_TEMP_L, int8_t AM_OF_SUB_L, int8_t LUM_INT_L, int8_t ANGLE_L,
             int8_t TIME_R, int8_t LENGTH_R, int8_t MASS_R, int8_t EL_CURR_R, int8_t TD_TEMP_R, int8_t AM_OF_SUB_R, int8_t LUM_INT_R, int8_t ANGLE_R>
    constexpr auto operator/(
        const BaseUnit<T_L, TIME_L, LENGTH_L, MASS_L, EL_CURR_L, TD_TEMP_L, AM_OF_SUB_L, LUM_INT_L, ANGLE_L> &lhs,
        const BaseUnit<T_R, TIME_R, LENGTH_R, MASS_R, EL_CURR_R, TD_TEMP_R, AM_OF_SUB_R, LUM_INT_R, ANGLE_R> &rhs)
        -> mapped_unit_t<BaseUnit<std::common_type_t<T_L, T_R>,
                                  TIME_L - TIME_R,
                                  LENGTH_L - LENGTH_R,
                                  MASS_L - MASS_R,
                                  EL_CURR_L - EL_CURR_R,
                                  TD_TEMP_L - TD_TEMP_R,
                                  AM_OF_SUB_L - AM_OF_SUB_R,
                                  LUM_INT_L - LUM_INT_R,
                                  ANGLE_L - ANGLE_R>> {
        using Result = mapped_unit_t<BaseUnit<std::common_type_t<T_L, T_R>,
                                              TIME_L - TIME_R,
                                              LENGTH_L - LENGTH_R,
                                              MASS_L - MASS_R,
                                              EL_CURR_L - EL_CURR_R,
                                              TD_TEMP_L - TD_TEMP_R,
                                              AM_OF_SUB_L - AM_OF_SUB_R,
                                              LUM_INT_L - LUM_INT_R,
                                              ANGLE_L - ANGLE_R>>;
        return Result(lhs.value() / rhs.value());
    }
} // namespace utl
