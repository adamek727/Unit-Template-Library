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

        explicit Angle(T angle, const TYPE &type = TYPE::RAD) {
            switch (type) {
                case TYPE::DEG:
                    this->set_value(angle / 180 * M_PI);
                    break;
                default:
                    this->set_value(angle);
                    break;
            }
        }

        explicit Angle(Length<T> s, Length<T> r) : Unit<T>{s.m() / r.m()} {};

        [[nodiscard]] auto rad() const -> T { return this->value(); }

        [[nodiscard]] auto deg() const -> T { return rad() / M_PI * 180.0; }

        auto operator+(const Angle &other) const -> Angle {
            return Angle(rad() + other.rad());
        }

        auto operator-(const Angle &other) const -> Angle {
            return Angle(rad() - other.rad());
        }

        auto operator*(T scalar) const -> Angle {
            return Angle(rad() * scalar);
        }

        auto operator/(T scalar) const -> Angle {
            return Angle(rad() / scalar);
        }

        friend auto operator*(T lhs, const Angle<T>& rhs) -> Angle<T>{
            return Angle<T>(rhs.rad() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<Unit<T>> {
        using type = Angle<T>;
    };
}