/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/force.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using PressureUnit = DivBaseUnits<T, Force<T>, Area<T>>;

    template<typename T>
    class Pressure : public PressureUnit<T> {

    public:
        explicit Pressure(T pressure) : PressureUnit<T>{pressure} {}

        explicit Pressure(const Force<T> &f, const Area<T> &a) : PressureUnit<T>{f.N() / a.m2()} {}

        [[nodiscard]] auto kPa() const -> T { return Pa() / KILO; }

        [[nodiscard]] auto hPa() const -> T { return Pa() / HECTO; }

        [[nodiscard]] auto Pa() const -> T { return this->value(); }

        auto operator+(const Pressure &other) const -> Pressure {
            return Pressure(Pa() + other.Pa());
        }

        auto operator-(const Pressure &other) const -> Pressure {
            return Pressure(Pa() - other.Pa());
        }

        auto operator*(const T scalar) const -> Pressure<T> {
            return Pressure(Pa() * scalar);
        }

        auto operator/(const T scalar) const -> Pressure<T> {
            return Pressure(Pa() / scalar);
        }

        auto operator*(const Area<T> &a) const -> Force<T> {
            return Force<T>(Pa() * a.m2());
        }

        friend auto operator*(T lhs, const Pressure<T>& rhs) -> Pressure<T> {
            return Pressure<T>(rhs.Pa() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<PressureUnit<T>> {
        using type = Pressure<T>;
    };
}