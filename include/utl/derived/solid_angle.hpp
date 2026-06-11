/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    class SolidAngle : public Unit<T> {
    public:

        constexpr explicit SolidAngle(T solid_angle) : Unit<T>{solid_angle} {}

        constexpr explicit SolidAngle(Area<T> a1, Area<T> a2) : Unit<T>{a1.m2() / a2.m2()} {};

        constexpr explicit SolidAngle(Area<T> a, Length<T> r) : Unit<T>{a.m2() / r.m() / r.m()} {};

        [[nodiscard]] constexpr auto sr() const -> T { return static_cast<T>(this->value()); }

        constexpr auto operator+(const SolidAngle &other) const -> SolidAngle {
            return SolidAngle(sr() + other.sr());
        }

        constexpr auto operator-(const SolidAngle &other) const -> SolidAngle {
            return SolidAngle(sr() - other.sr());
        }

        constexpr auto operator*(T scalar) const -> SolidAngle {
            return SolidAngle(sr() * scalar);
        }

        constexpr auto operator/(T scalar) const -> SolidAngle {
            return SolidAngle(sr() / scalar);
        }

        friend constexpr auto operator*(T lhs, const SolidAngle<T>& rhs) -> SolidAngle<T> {
            return SolidAngle<T>(rhs.sr() * lhs);
        }
    };
}