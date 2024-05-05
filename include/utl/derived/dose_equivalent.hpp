/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/absorbed_dose.hpp"

namespace utl {

    template<typename T>
    using DoseEquivalentUnit = DivBaseUnits<T, Energy<T>, Mass<T>>;

    template<typename T>
    class DoseEquivalent : public DoseEquivalentUnit<T> {

    public:
        explicit DoseEquivalent(T dose_eq) : DoseEquivalentUnit<T>{dose_eq} {}

        explicit DoseEquivalent(const AbsorbedDose<T> ad, const T radiation_weight_factor) : DoseEquivalentUnit<T>{ad.Gy() * radiation_weight_factor} {}

        [[nodiscard]] auto Sv() const -> T { return this->value(); }

        auto operator+(const DoseEquivalent &other) const -> DoseEquivalent {
            return DoseEquivalent(Sv() + other.Sv());
        }

        auto operator-(const DoseEquivalent &other) const -> DoseEquivalent {
            return DoseEquivalent(Sv() - other.Sv());
        }

        auto operator*(T scalar) const -> DoseEquivalent {
            return DoseEquivalent(Sv() * scalar);
        }

        auto operator/(T scalar) const -> DoseEquivalent {
            return DoseEquivalent(Sv() / scalar);
        }

        auto operator*(const Mass<T> &other) const -> Energy<T> {
            return EnerSv(Sv() * other.kg());
        }
    };
}