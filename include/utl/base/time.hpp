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
        explicit Time(T time) : TimeUnit<T>{time} {}

        [[nodiscard]] auto h() const -> T { return s() / SECS_IN_MINUTE / MINUTES_IN_HOUR; }

        [[nodiscard]] auto min() const -> T { return s() / SECS_IN_MINUTE; }

        [[nodiscard]] auto s() const -> T { return this->value(); }

        [[nodiscard]] auto ms() const -> T { return s() / MILLI; }

        [[nodiscard]] auto us() const -> T { return s() / MICRO; }

        [[nodiscard]] auto ns() const -> T { return s() / NANO; }

    };

    template<typename T>
    struct UnitMapper<TimeUnit<T>> {
        using type = Time<T>;
    };
}
