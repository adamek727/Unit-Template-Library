/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"
#include "utl/base/electric_current.hpp"
#include "utl/derived/voltage.hpp"

namespace utl {

    template<typename T>
    using ResistanceUnit = BaseUnit<T, -3, 2, 1, -2, 0, 0, 0>;

    template<typename T>
    class Resistance : public ResistanceUnit<T> {
    public:
        explicit Resistance(T res) : ResistanceUnit<T>{res} {}

        explicit Resistance(const Voltage<T> &v, const ElectricCurrent<T> &ec) : ResistanceUnit<T>{v.V() / ec.A()} {}

        [[nodiscard]] auto MOhm() const -> T { return this->value() / MEGA; }

        [[nodiscard]] auto kOhm() const -> T { return this->value() / KILO; }

        [[nodiscard]] auto Ohm() const -> T { return this->value(); }

        [[nodiscard]] auto mOhm() const -> T { return this->value() / MILLI; }

    };

    template<typename T>
    struct UnitMapper<ResistanceUnit<T>> {
        using type = Resistance<T>;
    };
}
