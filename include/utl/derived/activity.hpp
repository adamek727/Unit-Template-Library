/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    using ActivityUnit = BaseUnit<T, -1, 0, 0, 0, 0, 0, 0>;

    template<typename T>
    class Activity : public ActivityUnit<T> {

    public:
        constexpr explicit Activity(T activity) : ActivityUnit<T>{activity} {}

        [[nodiscard]] constexpr auto Bq() const -> T { return static_cast<T>(this->value()); }

        constexpr auto operator+(const Activity &other) const -> Activity {
            return Activity(Bq() + other.Bq());
        }

        constexpr auto operator-(const Activity &other) const -> Activity {
            return Activity(Bq() - other.Bq());
        }

        constexpr auto operator*(T scalar) const -> Activity {
            return Activity(Bq() * scalar);
        }

        constexpr auto operator/(T scalar) const -> Activity {
            return Activity(Bq() / scalar);
        }

        friend constexpr auto operator*(T lhs, const Activity<T> &rhs) -> Activity<T> {
            return Activity<T>(rhs.Bq() * lhs);
        }
    };

    //    template<typename T>
    //    struct UnitMapper<ActivityUnit<T>> {
    //        using type = Activity<T>;
    //    };
} // namespace utl