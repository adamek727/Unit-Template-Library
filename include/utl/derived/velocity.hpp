/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/all.hpp"

namespace utl {

    template<typename T>
    using VelocityUnit = BaseUnit<T, -1, 1, 0, 0, 0, 0, 0>;

    template<typename T>
    class Velocity : public VelocityUnit<T> {

        static constexpr double MPS_IN_MPH = 0.44704;

    public:
        constexpr Velocity() = default;

        constexpr explicit Velocity(T speed) : VelocityUnit<T>{speed} {}

        constexpr explicit Velocity(const Length<T> l, const Time<T> t) : VelocityUnit<T>{l.m() / t.s()} {}

        [[nodiscard]] constexpr auto mps() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mph() const -> T { return static_cast<T>(mps() / MPS_IN_MPH); }

        [[nodiscard]] constexpr auto kmph() const -> T { return static_cast<T>(this->value() * 3.6); }

    };

    template<typename T>
    struct UnitMapper<VelocityUnit<T>> {
        using type = Velocity<T>;
    };
}