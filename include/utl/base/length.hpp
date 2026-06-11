/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    using LengthUnit = BaseUnit<T, 0, 1, 0, 0, 0, 0, 0>;

    template<typename T>
    class Length : public LengthUnit<T> {

        static constexpr double METERS_IN_MILE = 1609.344;
        static constexpr double METERS_IN_YARD = 0.9144;
        static constexpr double METERS_IN_FOOT = 0.3048;
        static constexpr double METERS_IN_INCH = 0.0254;

    public:
        constexpr Length() = default;

        constexpr explicit Length(T length) : LengthUnit<T>{length} {}

        [[nodiscard]] constexpr auto km() const -> T { return static_cast<T>(m() / KILO); }

        [[nodiscard]] constexpr auto m() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mm() const -> T { return static_cast<T>(m() / MILLI); }

        [[nodiscard]] constexpr auto um() const -> T { return static_cast<T>(m() / MICRO); }

        [[nodiscard]] constexpr auto nm() const -> T { return static_cast<T>(m() / NANO); }

        [[nodiscard]] constexpr auto mi() const -> T { return static_cast<T>(m() / METERS_IN_MILE); }

        [[nodiscard]] constexpr auto yd() const -> T { return static_cast<T>(m() / METERS_IN_YARD); }

        [[nodiscard]] constexpr auto ft() const -> T { return static_cast<T>(m() / METERS_IN_FOOT); }

        [[nodiscard]] constexpr auto in() const -> T { return static_cast<T>(m() / METERS_IN_INCH); }

    };

    template<typename T>
    struct UnitMapper<LengthUnit<T>> {
        using type = Length<T>;
    };
}
