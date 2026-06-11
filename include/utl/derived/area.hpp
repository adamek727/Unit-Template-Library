/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"

namespace utl {

    template<typename T>
    using AreaUnit = BaseUnit<T, 0, 2, 0, 0, 0, 0, 0>;

    template<typename T>
    class Area : public AreaUnit<T> {

    public:
        constexpr Area() = default;

        constexpr explicit Area(T area) : AreaUnit<T>{area} {}

        constexpr explicit Area(const Length<T> l1, const Length<T> l2) : AreaUnit<T>{l1.m() * l2.m()} {}

        [[nodiscard]] constexpr auto km2() const -> T { return static_cast<T>(m2() / KILO / KILO); }

        [[nodiscard]] constexpr auto ha() const -> T { return static_cast<T>(a() / HECTO); }

        [[nodiscard]] constexpr auto a() const -> T { return static_cast<T>(m2() / HECTO); }

        [[nodiscard]] constexpr auto m2() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mm2() const -> T { return static_cast<T>(m2() / MILLI / MILLI); }

        [[nodiscard]] constexpr auto um2() const -> T { return static_cast<T>(m2() / MICRO / MICRO); }

        [[nodiscard]] constexpr auto nm2() const -> T { return static_cast<T>(m2() / NANO / NANO); }

    };

    template<typename T>
    struct UnitMapper<AreaUnit<T>> {
        using type = Area<T>;
    };
}
