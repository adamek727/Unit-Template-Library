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
        constexpr explicit Voltage(T voltage) : VoltageUnit<T>{voltage} {}

        constexpr explicit Voltage(const Power<T> &p, const ElectricCurrent<T> &ec = 1) : VoltageUnit<T>{p.W() / ec.A()} {}

        [[nodiscard]] constexpr auto V() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto kV() const -> T { return static_cast<T>(V() / KILO); }

        [[nodiscard]] constexpr auto mV() const -> T { return static_cast<T>(V() / MILLI); }
    };

    template<typename T>
    struct UnitMapper<VoltageUnit<T>> {
        using type = Voltage<T>;
    };
} // namespace utl