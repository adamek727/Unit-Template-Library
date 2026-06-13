/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/electric_charge.hpp"
#include "utl/derived/voltage.hpp"

namespace utl {

    template<typename T>
    using CapacitanceUnit = BaseUnit<T, 4, -2, -1, 2, 0, 0, 0>;

    template<typename T>
    class Capacitance : public CapacitanceUnit<T> {
    public:
        constexpr explicit Capacitance(T cap) : CapacitanceUnit<T>{cap} {}

        [[nodiscard]] constexpr auto F() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mF() const -> T { return static_cast<T>(F() / MILLI); }

        [[nodiscard]] constexpr auto uF() const -> T { return static_cast<T>(F() / MICRO); }

        [[nodiscard]] constexpr auto nF() const -> T { return static_cast<T>(F() / NANO); }

        [[nodiscard]] constexpr auto pF() const -> T { return static_cast<T>(F() / PICO); }
    };

    template<typename T>
    struct UnitMapper<CapacitanceUnit<T>> {
        using type = Capacitance<T>;
    };
} // namespace utl
