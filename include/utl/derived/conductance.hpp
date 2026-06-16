/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/resistance.hpp"

namespace utl {

    template<typename T>
    using ConductanceUnit = BaseUnit<T, 3, -2, -1, 2, 0, 0, 0>;

    template<typename T>
    class Conductance : public ConductanceUnit<T> {
    public:
        constexpr explicit Conductance(T cap) : ConductanceUnit<T>{cap} {}

        constexpr explicit Conductance(const ElectricCurrent<T> &ec, const Voltage<T> &v) : ConductanceUnit<T>{ec.A() / v.V()} {}

        [[nodiscard]] constexpr auto S() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<ConductanceUnit<T>> {
        using type = Conductance<T>;
    };
} // namespace utl
