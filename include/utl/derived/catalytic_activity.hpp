/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/amount_of_substance.hpp"
#include "utl/base/time.hpp"
#include "utl/derived/frequency.hpp"

namespace utl {

    template<typename T>
    using CatalyticActivityUnit = BaseUnit<T, -1, 0, 0, 0, 0, 1, 0>;

    template<typename T>
    class CatalyticActivity : public BaseUnit<T, -1, 0, 0, 0, 0, 1, 0> {
    public:
        constexpr CatalyticActivity() = default;

        constexpr explicit CatalyticActivity(T catalytic_activity) : CatalyticActivityUnit<T>{catalytic_activity} {}

        constexpr explicit CatalyticActivity(const AmountOfSubstance<T> &aos, const Time<T> &t) : CatalyticActivityUnit<T>{
                aos.mol() / t.s()} {}

        [[nodiscard]] constexpr auto katal() const -> T { return static_cast<T>(this->value()); }

    };

    template<typename T>
    struct UnitMapper<CatalyticActivityUnit<T>> {
        using type = CatalyticActivity<T>;
    };
}