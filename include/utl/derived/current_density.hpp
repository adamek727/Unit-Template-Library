/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using CurrentDensityUnit = BaseUnit<T, 0, -2, 0, 1, 0, 0, 0>;

    template<typename T>
    class CurrentDensity : public CurrentDensityUnit<T> {

    public:
        constexpr explicit CurrentDensity(T current_density) : CurrentDensityUnit<T>{current_density} {}

        constexpr explicit CurrentDensity(const ElectricCurrent<T> &i, const Area<T> &a) : CurrentDensityUnit<T>{i.A() / a.m2()} {}

        [[nodiscard]] constexpr auto Apm2() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<CurrentDensityUnit<T>> {
        using type = CurrentDensity<T>;
    };
} // namespace utl
