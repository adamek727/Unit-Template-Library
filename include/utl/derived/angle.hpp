/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <cmath>
#include "utl/base/length.hpp"

namespace utl {
    template<typename T>
    class Angle : public Unit<T> {
    public:
        enum class TYPE {
            RAD,
            DEG,
        };

        constexpr explicit Angle(T angle, const TYPE &type = TYPE::RAD) {
            switch (type) {
                case TYPE::DEG:
                    this->set_value(angle / 180 * M_PI);
                    break;
                default:
                    this->set_value(angle);
                    break;
            }
        }

        constexpr explicit Angle(Length<T> s, Length<T> r) : Unit<T>{s.m() / r.m()} {};

        [[nodiscard]] constexpr auto rad() const -> T { return this->value(); }

        [[nodiscard]] constexpr auto deg() const -> T { return rad() / M_PI * 180.0; }

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