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

        static constexpr double MILES_IN_KILOMETER = 0.6213711922;

    public:
        constexpr explicit Length(T length) : LengthUnit<T>{length} {}

        [[nodiscard]] constexpr auto km() const -> T { return m() / KILO; }

        [[nodiscard]] constexpr auto m() const -> T { return this->value(); }

        [[nodiscard]] constexpr auto mm() const -> T { return static_cast<T>(m() / MILLI); }

        [[nodiscard]] constexpr auto um() const -> T { return static_cast<T>(m() / MICRO); }

        [[nodiscard]] constexpr auto nm() const -> T { return static_cast<T>(m() / NANO); }

        [[nodiscard]] constexpr auto mi() const -> T { return km() * MILES_IN_KILOMETER; }

    };

    template<typename T>
    struct UnitMapper<LengthUnit<T>> {
        using type = Length<T>;
    };
}
