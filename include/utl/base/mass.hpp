/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using MassUnit = BaseUnit<T, 0, 0, 1, 0, 0, 0, 0>;

    template<typename T>
    class Mass : public MassUnit<T> {

        static constexpr double KILOGRAMS_IN_POUND = 0.45359237;
        static constexpr double KILOGRAMS_IN_OUNCE = 0.028349523125;

    public:
        constexpr explicit Mass(T mass) : MassUnit<T>{mass} {}

        [[nodiscard]] constexpr auto tonne() const -> T { return static_cast<T>(this->value() / KILO); }

        [[nodiscard]] constexpr auto kg() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto g() const -> T { return static_cast<T>(this->value() / MILLI); }

        [[nodiscard]] constexpr auto mg() const -> T { return static_cast<T>(this->value() / MICRO); }

        [[nodiscard]] constexpr auto ug() const -> T { return static_cast<T>(this->value() / NANO); }

        [[nodiscard]] constexpr auto lb() const -> T { return static_cast<T>(kg() / KILOGRAMS_IN_POUND); }

        [[nodiscard]] constexpr auto oz() const -> T { return static_cast<T>(kg() / KILOGRAMS_IN_OUNCE); }
    };

    template<typename T>
    struct UnitMapper<MassUnit<T>> {
        using type = Mass<T>;
    };
} // namespace utl
