/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/luminous_intensity.hpp"
#include "utl/derived/solid_angle.hpp"

namespace utl {
    template<typename T>
    class Illuminance;

    template<typename T>
    class Area;

    template<typename T>
    using LuminousFluxUnit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 1>;

    template<typename T>
    class LuminousFlux : public LuminousFluxUnit<T> {
    public:
        constexpr explicit LuminousFlux(T luminous_flux) : LuminousFluxUnit<T>{
                                                               luminous_flux} {}

        constexpr explicit LuminousFlux(const LuminousIntensity<T> &lum_int, const SolidAngle<T> &solid_angle)
            : LuminousFluxUnit<T>{
                  lum_int.cd() * solid_angle.sr()} {}

        [[nodiscard]] constexpr auto lm() const -> T { return static_cast<T>(this->value()); }

        constexpr auto operator+(const LuminousFlux &other) const -> LuminousFlux {
            return LuminousFlux(lm() + other.lm());
        }

        constexpr auto operator-(const LuminousFlux &other) const -> LuminousFlux {
            return LuminousFlux(lm() - other.lm());
        }

        constexpr auto operator*(T scalar) const -> LuminousFlux {
            return LuminousFlux(lm() * scalar);
        }

        constexpr auto operator/(T scalar) const -> LuminousFlux {
            return LuminousFlux(lm() / scalar);
        }

        constexpr auto operator/(LuminousIntensity<T> lum_int) const -> SolidAngle<T> {
            return SolidAngle<T>(lm() / lum_int.cd());
        }

        constexpr auto operator/(SolidAngle<T> solid_angle) const -> LuminousIntensity<T> {
            return LuminousIntensity<T>(lm() / solid_angle.sr());
        }

        constexpr auto operator/(Area<T> other) const -> Illuminance<T> {
            return Illuminance<T>(lm() / other.m2());
        }

        friend constexpr auto operator*(T lhs, const LuminousFlux<T> &rhs) -> LuminousFlux<T> {
            return LuminousFlux<T>(rhs.lm() * lhs);
        }
    };

} // namespace utl