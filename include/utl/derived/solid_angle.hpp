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

        explicit SolidAngle(T solid_angle) : Unit<T>{solid_angle} {}

        explicit SolidAngle(Area<T> a1, Area<T> a2) : Unit<T>{a1.m2() / a2.m2()} {};

        explicit SolidAngle(Area<T> a, Length<T> r) : Unit<T>{a.m2() / r.m() / r.m()} {};

        [[nodiscard]] auto sr() const -> T { return this->value(); }

        auto operator+(const SolidAngle &other) const -> SolidAngle {
            return SolidAngle(sr() + other.sr());
        }

        auto operator-(const SolidAngle &other) const -> SolidAngle {
            return SolidAngle(sr() - other.sr());
        }

        auto operator*(T scalar) const -> SolidAngle {
            return SolidAngle(sr() * scalar);
        }

        auto operator/(T scalar) const -> SolidAngle {
            return SolidAngle(sr() / scalar);
        }

        friend auto operator*(T lhs, const SolidAngle<T>& rhs) -> SolidAngle<T> {
            return SolidAngle<T>(rhs.sr() * lhs);
        }
    };
}