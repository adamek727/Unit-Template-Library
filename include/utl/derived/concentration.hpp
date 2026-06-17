/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/amount_of_substance.hpp"
#include "utl/derived/volume.hpp"

namespace utl {

    template<typename T>
    using ConcentrationUnit = BaseUnit<T, 0, -3, 0, 0, 0, 1, 0>;

    template<typename T>
    class Concentration : public ConcentrationUnit<T> {

    public:
        constexpr explicit Concentration(T concentration) : ConcentrationUnit<T>{concentration} {}

        constexpr explicit Concentration(const AmountOfSubstance<T> &n, const Volume<T> &v) : ConcentrationUnit<T>{n.mol() / v.m3()} {}

        [[nodiscard]] constexpr auto molpm3() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<ConcentrationUnit<T>> {
        using type = Concentration<T>;
    };
} // namespace utl
