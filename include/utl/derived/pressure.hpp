/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/force.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using PressureUnit = BaseUnit<T, -2, -1, 1, 0, 0, 0, 0>;

    template<typename T>
    class Pressure : public PressureUnit<T> {

    public:
        constexpr explicit Pressure(T pressure) : PressureUnit<T>{pressure} {}

        constexpr explicit Pressure(const Force<T> &f, const Area<T> &a) : PressureUnit<T>{f.N() / a.m2()} {}

        [[nodiscard]] constexpr auto kPa() const -> T { return static_cast<T>(Pa() / KILO); }

        [[nodiscard]] constexpr auto hPa() const -> T { return static_cast<T>(Pa() / HECTO); }

        [[nodiscard]] constexpr auto Pa() const -> T { return static_cast<T>(this->value()); }

    };

    template<typename T>
    struct UnitMapper<PressureUnit<T>> {
        using type = Pressure<T>;
    };
}