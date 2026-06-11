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

        [[nodiscard]] constexpr auto F() const -> T { return this->value(); }

        [[nodiscard]] constexpr auto mF() const -> T { return F() / MILLI; }

        [[nodiscard]] constexpr auto uF() const -> T { return F() / MICRO; }

        [[nodiscard]] constexpr auto nF() const -> T { return F() / NANO; }

        [[nodiscard]] constexpr auto pF() const -> T { return F() / PICO; }

    };

    template<typename T>
    struct UnitMapper<CapacitanceUnit<T>> {
        using type = Capacitance<T>;
    };
}
