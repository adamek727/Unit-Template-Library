/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/all.hpp"

namespace utl {

    template<typename T>
    class Acceleration;

    template<typename T>
    using VelocityUnit = DivBaseUnits<T, Length<T>, Time<T>>;

    template<typename T>
    class Velocity : public VelocityUnit<T> {

    public:
        explicit Velocity(T speed) : VelocityUnit<T>{speed} {}

        explicit Velocity(const Length<T> l, const Time<T> t) : VelocityUnit<T>{l.m() / t.s()} {}

        [[nodiscard]] auto mps() const -> T { return this->value(); }

        [[nodiscard]] auto kmph() const -> T { return this->value() * 3.6; }

        auto operator+(const Velocity &other) const -> Velocity {
            return Velocity(mps() + other.mps());
        }

        auto operator-(const Velocity &other) const -> Velocity {
            return Velocity(mps() - other.mps());
        }

        auto operator*(T scalar) const -> Velocity {
            return Velocity(mps() * scalar);
        }

        auto operator/(T scalar) const -> Velocity {
            return Velocity(mps() / scalar);
        }

        auto operator*(const Time<T> &other) const -> Length<T> {
            return Length<T>(mps() * other.s());
        }

        auto operator/(const Time<T> &other) const -> Acceleration<T> {
            return Acceleration<T>(mps() / other.s());
        }

        friend auto operator*(T lhs, const Velocity<T>& rhs) -> Velocity<T> {
            return Velocity<T>(rhs.mps() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<VelocityUnit<T>> {
        using type = Velocity<T>;
    };
}