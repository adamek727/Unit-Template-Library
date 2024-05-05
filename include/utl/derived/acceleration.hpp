/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/all.hpp"
#include "utl/derived/velocity.hpp"

namespace utl {

    template<typename T>
    using AccelerationUnit = DivBaseUnits<T, Velocity<T>, Time<T>>;

    template<typename T>
    class Acceleration : public AccelerationUnit<T> {

    public:
        explicit Acceleration(T acc) : AccelerationUnit<T>{acc} {}

        explicit Acceleration(const Velocity<T> v, const Time<T> t) : AccelerationUnit<T>{v.mps() / t.s()} {}

        [[nodiscard]] auto mps2() const -> T { return this->value(); }

        auto operator+(const Acceleration &other) const -> Acceleration {
            return Acceleration(mps2() + other.mps2());
        }

        auto operator-(const Acceleration &other) const -> Acceleration {
            return Acceleration(mps2() - other.mps2());
        }

        auto operator*(T scalar) const -> Acceleration {
            return Acceleration(mps2() * scalar);
        }

        auto operator/(T scalar) const -> Acceleration {
            return Acceleration(mps2() / scalar);
        }

        auto operator*(const Time<T> &other) const -> Velocity<T> {
            return Velocity<T>(mps2() * other.s());
        }

        friend auto operator*(T lhs, const Acceleration<T>& rhs) -> Acceleration<T> {
            return Acceleration<T>(rhs.mps2() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<AccelerationUnit<T>> {
        using type = Acceleration<T>;
    };
}