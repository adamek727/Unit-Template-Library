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
    using LuminousFluxUnit = DivBaseUnits<T, LuminousIntensity<T>, SolidAngle<T>>;

    template<typename T>
    class LuminousFlux : public LuminousFluxUnit<T> {
    public:
        explicit LuminousFlux(T luminous_flux) : LuminousFluxUnit<T>{
                luminous_flux} {}

        explicit LuminousFlux(const LuminousIntensity<T> &lum_int, const SolidAngle<T> &solid_angle)
                : LuminousFluxUnit<T>{
                lum_int.cd() * solid_angle.sr()} {}

        [[nodiscard]] auto lm() const -> T { return this->value(); }

        auto operator+(const LuminousFlux &other) const -> LuminousFlux {
            return LuminousFlux(lm() + other.lm());
        }

        auto operator-(const LuminousFlux &other) const -> LuminousFlux {
            return LuminousFlux(lm() - other.lm());
        }

        auto operator*(T scalar) const -> LuminousFlux {
            return LuminousFlux(lm() * scalar);
        }

        auto operator/(T scalar) const -> LuminousFlux {
            return LuminousFlux(lm() / scalar);
        }

        auto operator/(LuminousIntensity<T> lum_int) const -> SolidAngle<T> {
            return SolidAngle<T>(lm() / lum_int.cd());
        }

        auto operator/(SolidAngle<T> solid_angle) const -> LuminousIntensity<T> {
            return LuminousIntensity<T>(lm() / solid_angle.sr());
        }

        auto operator/(Area<T> other) const -> Illuminance<T> {
            return Illuminance<T>(lm() / other.m2());
        }

        friend auto operator*(T lhs, const LuminousFlux<T>& rhs) -> LuminousFlux<T> {
            return LuminousFlux<T>(rhs.lm() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<LuminousFluxUnit<T>> {
        using type = LuminousFlux<T>;
    };
}