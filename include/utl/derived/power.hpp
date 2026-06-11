/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"
#include "utl/derived/energy.hpp"
#include "utl/derived/frequency.hpp"

namespace utl {

    template<typename T>
    using PowerUnit = BaseUnit<T, -3, 2, 1, 0, 0, 0, 0>;

    template<typename T>
    class Power : public PowerUnit<T> {

        static constexpr double WATTS_IN_HORSEPOWER = 745.6998715822702;

    public:
        constexpr Power() = default;

        constexpr explicit Power(T power) : PowerUnit<T>{power} {}

        constexpr explicit Power(const Energy<T> &e, const Time<T> &t) : PowerUnit<T>{e.J() / t.s()} {}

        [[nodiscard]] constexpr auto kW() const -> T { return static_cast<T>(W() / KILO); }

        [[nodiscard]] constexpr auto W() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto hp() const -> T { return static_cast<T>(W() / WATTS_IN_HORSEPOWER); }

    };

    template<typename T>
    struct UnitMapper<PowerUnit<T>> {
        using type = Power<T>;
    };
}