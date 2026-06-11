/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <cstdint>
#include <ostream>
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    auto operator<<(std::ostream &os, const BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT> &unit) -> std::ostream & {
        static constexpr const char *symbols[7] = {"s", "m", "kg", "A", "K", "mol", "cd"};
        os << unit.value() << " [";
        auto dims = unit.dim();
        bool empty = true;
        for (std::size_t i = 0; i < dims.size(); ++i) {
            if (dims[i] == 0) {
                continue;
            }
            if (!empty) {
                os << " ";
            }
            os << symbols[i];
            if (dims[i] != 1) {
                os << "^" << static_cast<int>(dims[i]);
            }
            empty = false;
        }
        if (empty) {
            os << "-";
        }
        os << "]";
        return os;
    }
}
