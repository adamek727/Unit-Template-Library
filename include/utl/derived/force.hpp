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
        explicit Force(T force) : ForceUnit<T>{force} {}

        explicit Force(const Mass<T> &m, const Acceleration<T> &acc) : ForceUnit<T>{m.kg() * acc.mps2()} {}

        [[nodiscard]] auto kN() const -> T { return N() / KILO; }

        [[nodiscard]] auto N() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<ForceUnit<T>> {
        using type = Force<T>;
    };
}