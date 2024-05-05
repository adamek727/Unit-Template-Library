/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/base/time.hpp"

namespace utl {


    template<typename T>
    using ElectricChangeUnit = MulBaseUnits<T, ElectricCurrent<T>, Time<T>>;

    template<typename T>
    class ElectricCharge : public ElectricChangeUnit<T> {
    public:
        explicit ElectricCharge(const T &charge) : ElectricChangeUnit<T>{charge} {}

        explicit ElectricCharge(const ElectricCurrent<T> &ec, const Time<T> &t) : ElectricChangeUnit<T>{
                ec.A() * t.s()} {}

        [[nodiscard]] auto C() const -> T { return this->value(); }

        auto operator+(const ElectricCharge &other) const -> ElectricCharge {
            return ElectricCharge(C() + other.C());
        }

        auto operator-(const ElectricCharge &other) const -> ElectricCharge {
            return ElectricCharge(C() - other.C());
        }

        auto operator*(T scalar) const -> ElectricCharge {
            return ElectricCharge(C() * scalar);
        }

        auto operator/(T scalar) const -> ElectricCharge {
            return ElectricCharge(C() / scalar);
        }

        auto operator/(const ElectricCurrent<T> &other) const -> Time<T> {
            return Time<T>(C() / other.A());
        }

        auto operator/(const Time<T> &other) const -> ElectricCurrent<T> {
            return ElectricCurrent<T>(C() / other.s());
        }

        friend auto operator*(T lhs, const ElectricCharge<T>& rhs) -> ElectricCharge {
            return ElectricCharge<T>(rhs.C() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<ElectricCharge<T>> {
        using type = ElectricCharge<T>;
    };
}
