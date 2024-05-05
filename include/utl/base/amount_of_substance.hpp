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
        explicit AmountOfSubstance(T amount_of_sub) : AmountOfSubstanceUnit<T>{amount_of_sub} {}

        [[nodiscard]] auto mol() const -> T { return this->value(); }

        [[nodiscard]] auto mmol() const -> T { return mol() / MILLI; }

        [[nodiscard]] auto umol() const -> T { return mol() / MICRO; }

        [[nodiscard]] auto nmol() const -> T { return mol() / NANO; }

        auto operator+(const AmountOfSubstance &other) const -> AmountOfSubstance {
            return AmountOfSubstance(mol() + other.mol());
        }

        auto operator-(const AmountOfSubstance &other) const -> AmountOfSubstance {
            return AmountOfSubstance(mol() - other.mol());
        }

        auto operator*(T scalar) const -> AmountOfSubstance {
            return AmountOfSubstance(mol() * scalar);
        }

        auto operator/(T scalar) const -> AmountOfSubstance {
            return AmountOfSubstance(mol() / scalar);
        }

        friend auto operator*(T lhs, const AmountOfSubstance<T>& rhs) -> AmountOfSubstance<T> {
            return AmountOfSubstance<T>(rhs.mol() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<AmountOfSubstanceUnit<T>> {
        using type = AmountOfSubstance<T>;
    };
}