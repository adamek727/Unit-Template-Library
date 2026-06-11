/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using ElectricCurrentUnit = BaseUnit<T, 0, 0, 0, 1, 0, 0, 0>;

    template<typename T>
    class ElectricCurrent : public ElectricCurrentUnit<T> {
    public:
        constexpr ElectricCurrent() = default;

        constexpr explicit ElectricCurrent(T current) : ElectricCurrentUnit<T>{current} {}

        [[nodiscard]] constexpr auto kA() const -> T { return static_cast<T>(A() / KILO); }

        [[nodiscard]] constexpr auto A() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mA() const -> T { return static_cast<T>(A() / MILLI ); }

        [[nodiscard]] constexpr auto uA() const -> T { return static_cast<T>(A() / MICRO); }

        [[nodiscard]] constexpr auto nA() const -> T { return static_cast<T>(A() / NANO); }

    };

    template<typename T>
    struct UnitMapper<ElectricCurrentUnit<T>> {
        using type = ElectricCurrent<T>;
    };
}
