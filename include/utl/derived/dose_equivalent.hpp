/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/absorbed_dose.hpp"

namespace utl {

    struct DoseEquivalentKind {};

    template<typename T>
    using DoseEquivalentUnit = BaseUnit<T, -2, 2, 0, 0, 0, 0, 0, 0, DoseEquivalentKind>;

    template<typename T>
    class DoseEquivalent : public DoseEquivalentUnit<T> {

    public:
        constexpr explicit DoseEquivalent(T dose_eq) : DoseEquivalentUnit<T>{dose_eq} {}

        constexpr explicit DoseEquivalent(const AbsorbedDose<T> ad, const T radiation_weight_factor) : DoseEquivalentUnit<T>{ad.Gy() * radiation_weight_factor} {}

        [[nodiscard]] constexpr auto Sv() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<DoseEquivalentUnit<T>> {
        using type = DoseEquivalent<T>;
    };
} // namespace utl