/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    class Frequency;


    template<typename T>
    using TimeTemperatureUnit = BaseUnit<T, 1, 0, 0, 0, 0, 0, 0>;

    template<typename T>
    class Time : public TimeTemperatureUnit<T> {

    public:
        explicit Time(T time) : TimeTemperatureUnit<T>{time} {}

        [[nodiscard]] auto h() const -> T { return s() / SECS_IN_MINUTE / MINUTES_IN_HOUR; }

        [[nodiscard]] auto min() const -> T { return s() / SECS_IN_MINUTE; }

        [[nodiscard]] auto s() const -> T { return this->value(); }

        [[nodiscard]] auto ms() const -> T { return s() / MILLI; }

        [[nodiscard]] auto us() const -> T { return s() / MICRO; }

        [[nodiscard]] auto ns() const -> T { return s() / NANO; }

        auto operator+(const Time &other) const -> Time {
            return Time(s() + other.s());
        }

        auto operator-(const Time &other) const -> Time {
            return Time(s() - other.s());
        }

        auto operator*(T scalar) const -> Time {
            return Time(s() * scalar);
        }

        auto operator/(T scalar) const -> Time {
            return Time(s() / scalar);
        }

        friend auto operator*(T lhs, const Time<T>& rhs) -> Time<T> {
            return Time<T>(rhs.s() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<BaseUnit<T, 1, 0, 0, 0, 0, 0, 0>> {
        using type = Time<T>;
    };
}
