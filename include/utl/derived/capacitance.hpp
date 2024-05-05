/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/electric_charge.hpp"
#include "utl/derived/voltage.hpp"

namespace utl {

    template<typename T>
    using CapacitanceUnit = DivBaseUnits<T, ElectricCharge<T>, Voltage<T>>;

    template<typename T>
    class Capacitance : public CapacitanceUnit<T> {
    public:
        explicit Capacitance(T cap) : CapacitanceUnit<T>{cap} {}

        [[nodiscard]] auto F() const -> T { return this->value(); }

        [[nodiscard]] auto mF() const -> T { return F() / MILLI; }

        [[nodiscard]] auto uF() const -> T { return F() / MICRO; }

        [[nodiscard]] auto nF() const -> T { return F() / NANO; }

        [[nodiscard]] auto pF() const -> T { return F() / PICO; }

        auto operator+(const Capacitance &other) const -> Capacitance {
            return Capacitance(F() + other.F());
        }

        auto operator-(const Capacitance &other) const -> Capacitance {
            return Capacitance(F() - other.F());
        }

        auto operator*(T scalar) const -> Capacitance {
            return Capacitance(F() * scalar);
        }

        auto operator/(T scalar) const -> Capacitance {
            return Capacitance(F() / scalar);
        }

        auto operator*(const Voltage<T> &other) const -> ElectricCharge<T> {
            return ElectricCharge<T>(F() * other.V());
        }

        friend auto operator*(T lhs, const Capacitance<T>& rhs) -> Capacitance<T> {
            return Capacitance<T>(rhs.F() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<Capacitance<T>> {
        using type = Capacitance<T>;
    };
}
