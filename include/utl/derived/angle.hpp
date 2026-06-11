/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"

namespace utl {
    template<typename T>
    class Angle : public Unit<T> {
    public:
        enum class TYPE {
            RAD,
            DEG,
        };

    private:
        static constexpr auto to_rad(T angle, const TYPE &type) -> T {
            switch (type) {
                case TYPE::DEG:
                    return static_cast<T>(angle / 180 * PI);
                default:
                    return angle;
            }
        }

    public:
        constexpr explicit Angle(T angle, const TYPE &type = TYPE::RAD)
            : Unit<T>{to_rad(angle, type)} {}

        constexpr explicit Angle(Length<T> s, Length<T> r) : Unit<T>{s.m() / r.m()} {};

        [[nodiscard]] constexpr auto rad() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto deg() const -> T { return static_cast<T>(rad() / PI * 180.0); }

        constexpr auto operator+(const Angle &other) const -> Angle {
            return Angle(rad() + other.rad());
        }

        constexpr auto operator-(const Angle &other) const -> Angle {
            return Angle(rad() - other.rad());
        }

        constexpr auto operator*(T scalar) const -> Angle {
            return Angle(rad() * scalar);
        }

        constexpr auto operator/(T scalar) const -> Angle {
            return Angle(rad() / scalar);
        }

        friend constexpr auto operator*(T lhs, const Angle<T>& rhs) -> Angle<T>{
            return Angle<T>(rhs.rad() * lhs);
        }
    };

}