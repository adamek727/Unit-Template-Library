/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/resistance.hpp"

namespace utl {

    template<typename T>
    using ConductanceUnit = InvBaseUnit<T, Resistance<T>>;

    template<typename T>
    class Conductance : public ConductanceUnit<T> {
    public:
        explicit Conductance(T cap) : ConductanceUnit<T>{cap} {}

        explicit Conductance(const ElectricCurrent<T> &ec, const Voltage<T> &v) : ConductanceUnit<T>{ec.A() / v.V()} {}

        [[nodiscard]] auto S() const -> T { return this->value(); }

        auto operator+(const Conductance &other) const -> Conductance {
            return Conductance(S() + other.S());
        }

        auto operator-(const Conductance &other) const -> Conductance {
            return Conductance(S() - other.S());
        }

        auto operator*(T scalar) const -> Conductance {
            return Conductance(S() * scalar);
        }

        auto operator/(T scalar) const -> Conductance {
            return Conductance(S() / scalar);
        }

        auto operator*(const Voltage<T> &other) const -> ElectricCurrent<T> {
            return ElectricCurrent<T>(S() * other.V());
        }

        friend auto operator*(T lhs, const Conductance<T>& rhs) -> Conductance {
            return Conductance<T>(rhs.S() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<ConductanceUnit<T>> {
        using type = Conductance<T>;
    };
}
