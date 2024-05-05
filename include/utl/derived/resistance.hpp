/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"
#include "utl/base/electric_current.hpp"
#include "utl/derived/voltage.hpp"

namespace utl {

    template<typename T>
    class Conductance;

    template<typename T>
    using ResistanceUnit = DivBaseUnits<T, Voltage<T>, ElectricCurrent<T>>;

    template<typename T>
    class Resistance : public ResistanceUnit<T> {
    public:
        explicit Resistance(T res) : ResistanceUnit<T>{res} {}

        explicit Resistance(const Voltage<T> &v, const ElectricCurrent<T> &ec) : ResistanceUnit<T>{v.V() / ec.A()} {}

        [[nodiscard]] auto MOhm() const -> T { return this->value() / MEGA; }

        [[nodiscard]] auto kOhm() const -> T { return this->value() / KILO; }

        [[nodiscard]] auto Ohm() const -> T { return this->value(); }

        [[nodiscard]] auto mOhm() const -> T { return this->value() / MILLI; }

        auto operator+(const Resistance &other) const -> Resistance {
            return Resistance(Ohm() + other.Ohm());
        }

        auto operator-(const Resistance &other) const -> Resistance {
            return Resistance(Ohm() - other.Ohm());
        }

        auto operator*(T scalar) const -> Resistance {
            return Resistance(Ohm() * scalar);
        }

        auto operator/(T scalar) const -> Resistance {
            return Resistance(Ohm() / scalar);
        }

        auto operator*(const ElectricCurrent<T> &other) const -> Voltage<T> {
            return Voltage<T>(Ohm() * other.A());
        }

        friend auto operator*(T lhs, const Resistance<T>& rhs) -> Resistance<T> {
            return Resistance<T>(rhs.Ohm() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<ResistanceUnit<T>> {
        using type = Resistance<T>;
    };
}
