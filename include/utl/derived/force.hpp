/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/mass.hpp"
#include "utl/derived/acceleration.hpp"

namespace utl {

    template<typename T>
    using ForceUnit = BaseUnit<T, -2, 1, 1, 0, 0, 0, 0>;

    template<typename T>
    class Force : public ForceUnit<T> {

    public:
        constexpr explicit Force(T force) : ForceUnit<T>{force} {}

        constexpr explicit Force(const Mass<T> &m, const Acceleration<T> &acc) : ForceUnit<T>{m.kg() * acc.mps2()} {}

        [[nodiscard]] constexpr auto kN() const -> T { return static_cast<T>(N() / KILO); }

        [[nodiscard]] constexpr auto N() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<ForceUnit<T>> {
        using type = Force<T>;
    };
} // namespace utl