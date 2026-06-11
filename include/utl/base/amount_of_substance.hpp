/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using AmountOfSubstanceUnit = BaseUnit<T, 0, 0, 0, 0, 0, 1, 0>;

    template<typename T>
    class AmountOfSubstance : public AmountOfSubstanceUnit<T> {
    public:
        constexpr explicit AmountOfSubstance(T amount_of_sub) : AmountOfSubstanceUnit<T>{amount_of_sub} {}

        [[nodiscard]] constexpr auto mol() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mmol() const -> T { return static_cast<T>(mol() / MILLI); }

        [[nodiscard]] constexpr auto umol() const -> T { return static_cast<T>(mol() / MICRO); }

        [[nodiscard]] constexpr auto nmol() const -> T { return static_cast<T>(mol() / NANO); }

    };

    template<typename T>
    struct UnitMapper<AmountOfSubstanceUnit<T>> {
        using type = AmountOfSubstance<T>;
    };
}