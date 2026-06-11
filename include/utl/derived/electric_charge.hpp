/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    using ElectricChargeUnit = BaseUnit<T, 1, 0, 0, 1, 0, 0, 0>;

    template<typename T>
    class ElectricCharge : public ElectricChargeUnit<T> {
    public:
        explicit ElectricCharge(const T &charge) : ElectricChargeUnit<T>{charge} {}

        explicit ElectricCharge(const ElectricCurrent<T> &ec, const Time<T> &t) : ElectricChargeUnit<T>{
                ec.A() * t.s()} {}

        [[nodiscard]] auto C() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<ElectricChargeUnit<T>> {
        using type = ElectricCharge<T>;
    };
}
