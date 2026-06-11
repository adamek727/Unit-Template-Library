/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/absorbed_dose.hpp"

namespace utl {

    template<typename T>
    using DoseEquivalentUnit = BaseUnit<T, -2, 2, 0, 0, 0, 0, 0>;

    template<typename T>
    class DoseEquivalent : public DoseEquivalentUnit<T> {

    public:
        constexpr explicit DoseEquivalent(T dose_eq) : DoseEquivalentUnit<T>{dose_eq} {}

        constexpr explicit DoseEquivalent(const AbsorbedDose<T> ad, const T radiation_weight_factor) : DoseEquivalentUnit<T>{ad.Gy() * radiation_weight_factor} {}

        [[nodiscard]] constexpr auto Sv() const -> T { return this->value(); }

        constexpr auto operator+(const DoseEquivalent &other) const -> DoseEquivalent {
            return DoseEquivalent(Sv() + other.Sv());
        }

        constexpr auto operator-(const DoseEquivalent &other) const -> DoseEquivalent {
            return DoseEquivalent(Sv() - other.Sv());
        }

        constexpr auto operator*(T scalar) const -> DoseEquivalent {
            return DoseEquivalent(Sv() * scalar);
        }

        constexpr auto operator/(T scalar) const -> DoseEquivalent {
            return DoseEquivalent(Sv() / scalar);
        }

        friend constexpr auto operator*(T lhs, const DoseEquivalent<T> &rhs) -> DoseEquivalent<T> {
            return DoseEquivalent<T>(rhs.Sv() * lhs);
        }
    };
}