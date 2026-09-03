/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    struct ActivityKind {};

    template<typename T>
    using ActivityUnit = BaseUnit<T, -1, 0, 0, 0, 0, 0, 0, 0, ActivityKind>;

    template<typename T>
    class Activity : public ActivityUnit<T> {

    public:
        constexpr explicit Activity(T activity) : ActivityUnit<T>{activity} {}

        [[nodiscard]] constexpr auto Bq() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<ActivityUnit<T>> {
        using type = Activity<T>;
    };
} // namespace utl