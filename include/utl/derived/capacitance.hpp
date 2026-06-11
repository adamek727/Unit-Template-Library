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
        explicit Capacitance(T cap) : CapacitanceUnit<T>{cap} {}

        [[nodiscard]] auto F() const -> T { return this->value(); }

        [[nodiscard]] auto mF() const -> T { return F() / MILLI; }

        [[nodiscard]] auto uF() const -> T { return F() / MICRO; }

        [[nodiscard]] auto nF() const -> T { return F() / NANO; }

        [[nodiscard]] auto pF() const -> T { return F() / PICO; }

    };

    template<typename T>
    struct UnitMapper<CapacitanceUnit<T>> {
        using type = Capacitance<T>;
    };
}
