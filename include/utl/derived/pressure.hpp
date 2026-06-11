/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/force.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using PressureUnit = BaseUnit<T, -2, -1, 1, 0, 0, 0, 0>;

    template<typename T>
    class Pressure : public PressureUnit<T> {

    public:
        explicit Pressure(T pressure) : PressureUnit<T>{pressure} {}

        explicit Pressure(const Force<T> &f, const Area<T> &a) : PressureUnit<T>{f.N() / a.m2()} {}

        [[nodiscard]] auto kPa() const -> T { return Pa() / KILO; }

        [[nodiscard]] auto hPa() const -> T { return Pa() / HECTO; }

        [[nodiscard]] auto Pa() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<PressureUnit<T>> {
        using type = Pressure<T>;
    };
}