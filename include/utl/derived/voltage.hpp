/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/derived/power.hpp"

namespace utl {

    template<typename T>
    using VoltageUnit = BaseUnit<T, -3, 2, 1, -1, 0, 0, 0>;

    template<typename T>
    class Voltage : public VoltageUnit<T> {
    public:
        explicit Voltage(T voltage) : VoltageUnit<T>{voltage} {}

        explicit Voltage(const Power<T> &p, const ElectricCurrent<T> &ec = 1) : VoltageUnit<T>{p.W() / ec.A()} {}

        [[nodiscard]] auto V() const -> T { return this->value(); }

        [[nodiscard]] auto kV() const -> T { return V() / KILO; }

        [[nodiscard]] auto mV() const -> T { return V() / MILLI; }

    };

    template<typename T>
    struct UnitMapper<VoltageUnit<T>> {
        using type = Voltage<T>;
    };
}