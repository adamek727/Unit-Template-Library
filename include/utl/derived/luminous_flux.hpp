/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/luminous_intensity.hpp"
#include "utl/derived/solid_angle.hpp"

namespace utl {

    template<typename T>
    using LuminousFluxUnit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 1, 2>;

    template<typename T>
    class LuminousFlux : public LuminousFluxUnit<T> {
    public:
        constexpr explicit LuminousFlux(T luminous_flux) : LuminousFluxUnit<T>{
                                                               luminous_flux} {}

        constexpr explicit LuminousFlux(const LuminousIntensity<T> &lum_int, const SolidAngle<T> &solid_angle)
            : LuminousFluxUnit<T>{
                  lum_int.cd() * solid_angle.sr()} {}

        [[nodiscard]] constexpr auto lm() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<LuminousFluxUnit<T>> {
        using type = LuminousFlux<T>;
    };

} // namespace utl