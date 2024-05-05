/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/mass.hpp"
#include "utl/derived/acceleration.hpp"

namespace utl {

    template<typename T>
    class Pressure;

    template<typename T>
    class Energy;


    template<typename T>
    using ForceUnit = MulBaseUnits<T, Mass<T>, Acceleration<T>>;

    template<typename T>
    class Force : public ForceUnit<T> {

    public:
        explicit Force(T force) : ForceUnit<T>{force} {}

        explicit Force(const Mass<T> &m, const Acceleration<T> &acc) : ForceUnit<T>{m.kg() * acc.mps2()} {}

        [[nodiscard]] auto kN() const -> T { return N() / KILO; }

        [[nodiscard]] auto N() const -> T { return this->value(); }

        auto operator+(const Force &other) const -> Force {
            return Force(N() + other.N());
        }

        auto operator-(const Force &other) const -> Force {
            return Force(N() - other.N());
        }

        auto operator*(const T scalar) const -> Force<T> {
            return Force(N() * scalar);
        }

        auto operator/(const T scalar) const -> Force<T> {
            return Force(N() / scalar);
        }


        auto operator/(const Acceleration<T> &other) const -> Mass<T> {
            return Mass<T>(N() / other.mps2());
        }

        auto operator/(const Mass<T> &other) const -> Acceleration<T> {
            return Acceleration<T>(N() / other.kg());
        }

        auto operator*(const Length<T> &other) const -> Energy<T> {
            return Energy<T>(N() * other.m());
        }

        auto operator/(const Area<T> &other) const -> Pressure<T> {
            return Pressure<T>(N() / other.m2());
        }

        friend auto operator*(T lhs, const Force<T>& rhs) -> Force {
            return Force<T>(rhs.N() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<ForceUnit<T>> {
        using type = Force<T>;
    };
}