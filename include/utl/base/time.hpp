/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using TimeUnit = BaseUnit<T, 1, 0, 0, 0, 0, 0, 0>;

    template<typename T>
    class Time : public TimeUnit<T> {

    public:
        constexpr explicit Time(T time) : TimeUnit<T>{time} {}

        [[nodiscard]] constexpr auto day() const -> T { return static_cast<T>(h() / HOURS_IN_DAY); }

        [[nodiscard]] constexpr auto h() const -> T { return static_cast<T>(s() / SECS_IN_MINUTE / MINUTES_IN_HOUR); }

        [[nodiscard]] constexpr auto min() const -> T { return static_cast<T>(s() / SECS_IN_MINUTE); }

        [[nodiscard]] constexpr auto s() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto ms() const -> T { return static_cast<T>(s() / MILLI); }

        [[nodiscard]] constexpr auto us() const -> T { return static_cast<T>(s() / MICRO); }

        [[nodiscard]] constexpr auto ns() const -> T { return static_cast<T>(s() / NANO); }
    };

    template<typename T>
    struct UnitMapper<TimeUnit<T>> {
        using type = Time<T>;
    };
} // namespace utl
