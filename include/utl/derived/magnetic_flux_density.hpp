/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/area.hpp"
#include "utl/derived/magnetic_flux.hpp"

namespace utl {

    template<typename T>
    class MagneticFluxDensity;

    template<typename T>
    using MagneticFluxDensityUnit = BaseUnit<T, -2, 0, 1, -1, 0, 0, 0>;

    template<typename T>
    class MagneticFluxDensity : public MagneticFluxDensityUnit<T> {
    public:
        constexpr MagneticFluxDensity() = default;

        constexpr explicit MagneticFluxDensity(T illuminance) : MagneticFluxDensityUnit<T>{illuminance} {}

        constexpr explicit MagneticFluxDensity(const MagneticFlux<T> &mf, const Area<T> &a) : MagneticFluxDensityUnit<T>{
                mf.Wb() / a.m2()} {}

        [[nodiscard]] constexpr auto Tesla() const -> T { return static_cast<T>(this->value()); }

    };

    template<typename T>
    struct UnitMapper<MagneticFluxDensityUnit<T>> {
        using type = MagneticFluxDensity<T>;
    };
}