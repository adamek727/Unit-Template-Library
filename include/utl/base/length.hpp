/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    class Area;

    template<typename T>
    class Volume;

    template<typename T>
    class Velocity;

    template<typename T>
    using LengthUnit = BaseUnit<T, 0, 1, 0, 0, 0, 0, 0>;

    template<typename T>
    class Length : public LengthUnit<T> {

        static constexpr double MILES_IN_KILOMETER = 0.6213711922;

    public:
        explicit Length(T length) : LengthUnit<T>{length} {}

        [[nodiscard]] auto km() const -> T { return m() / KILO; }

        [[nodiscard]] auto m() const -> T { return this->value(); }

        [[nodiscard]] auto mm() const -> T { return static_cast<T>(m() / MILLI); }

        [[nodiscard]] auto um() const -> T { return static_cast<T>(m() / MICRO); }

        [[nodiscard]] auto nm() const -> T { return static_cast<T>(m() / NANO); }

        [[nodiscard]] auto mi() const -> T { return km() * MILES_IN_KILOMETER; }

        auto operator+(const Length &other) const -> Length {
            return Length(m() + other.m());
        }

        auto operator-(const Length &other) const -> Length {
            return Length(m() - other.m());
        }

        auto operator*(T scalar) const -> Length {
            return Length(m() * scalar);
        }

        auto operator/(T scalar) const -> Length {
            return Length(m() / scalar);
        }

        auto operator*(const Length &other) const -> Area<T> {
            return Area<T>(m() * other.m());
        }

        auto operator*(const Area<T> &other) const -> Volume<T> {
            return Volume<T>(m() * other.m2());
        }

        auto operator/(const Time<T> &other) const -> Velocity<T> {
            return Velocity<T>(m() / other.s());
        }

        friend auto operator*(T lhs, const Length<T>& rhs) -> Length<T> {
            return Length<T>(rhs.m() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<LengthUnit<T>> {
        using type = Length<T>;
    };
}
