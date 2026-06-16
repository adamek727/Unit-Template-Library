/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <cmath>
#include "utl/base/length.hpp"

namespace utl {

    template<typename T>
    using AngleUnit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 0, 1>;

    template<typename T>
    class Angle : public AngleUnit<T> {
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
            : AngleUnit<T>{to_rad(angle, type)} {}

        constexpr explicit Angle(Length<T> s, Length<T> r) : AngleUnit<T>{s.m() / r.m()} {};

        [[nodiscard]] constexpr auto rad() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto deg() const -> T { return static_cast<T>(rad() / PI * 180.0); }
    };

    template<typename T>
    struct UnitMapper<AngleUnit<T>> {
        using type = Angle<T>;
    };

    template<typename T>
    auto sin(const Angle<T> &angle) -> T { return static_cast<T>(std::sin(angle.rad())); }

    template<typename T>
    auto cos(const Angle<T> &angle) -> T { return static_cast<T>(std::cos(angle.rad())); }

    template<typename T>
    auto tan(const Angle<T> &angle) -> T { return static_cast<T>(std::tan(angle.rad())); }

} // namespace utl
