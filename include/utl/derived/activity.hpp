/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    using ActivityUnit = InvBaseUnit<T, Time<T>>;

    template<typename T>
    class Activity : public ActivityUnit<T> {

    public:
        explicit Activity(T activity) : ActivityUnit<T>{activity} {}

        [[nodiscard]] auto Bq() const -> T { return this->value(); }

        auto operator+(const Activity &other) const -> Activity {
            return Activity(Bq() + other.Bq());
        }

        auto operator-(const Activity &other) const -> Activity {
            return Activity(Bq() - other.Bq());
        }

        auto operator*(T scalar) const -> Activity {
            return Activity(Bq() * scalar);
        }

        auto operator/(T scalar) const -> Activity {
            return Activity(Bq() / scalar);
        }

        friend auto operator*(T lhs, const Activity<T>& rhs) -> Activity<T> {
            return Activity<T>(rhs.Bq() * lhs);
        }
    };

//    template<typename T>
//    struct UnitMapper<ActivityUnit<T>> {
//        using type = Activity<T>;
//    };
}