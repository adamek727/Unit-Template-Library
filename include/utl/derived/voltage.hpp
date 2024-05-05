/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/derived/power.hpp"

namespace utl {

    template<typename T>
    using VoltageUnit = DivBaseUnits<T, Power<T>, ElectricCurrent<T>>;

    template<typename T>
    class Voltage : public VoltageUnit<T> {
    public:
        explicit Voltage(T voltage) : VoltageUnit<T>{voltage} {}

        explicit Voltage(const Power<T> &p, const ElectricCurrent<T> &ec = 1) : VoltageUnit<T>{p.W() / ec.A()} {}

        [[nodiscard]] auto V() const -> T { return this->value(); }

        [[nodiscard]] auto kV() const -> T { return V() / KILO; }

        [[nodiscard]] auto mV() const -> T { return V() / MILLI; }

        auto operator+(const Voltage &other) const -> Voltage {
            return Voltage(V() + other.V());
        }

        auto operator-(const Voltage &other) const -> Voltage {
            return Voltage(V() - other.V());
        }

        auto operator*(T scalar) const -> Voltage {
            return Voltage(V() * scalar);
        }

        auto operator/(T scalar) const -> Voltage {
            return Voltage(V() / scalar);
        }

        auto operator*(const ElectricCurrent<T> &other) const -> Power<T> {
            return Power<T>(V() * other.A());
        }

        friend auto operator*(T lhs, const Voltage<T>& rhs) -> Voltage<T> {
            return Voltage<T>(rhs.V() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<VoltageUnit<T>> {
        using type = Voltage<T>;
    };
}