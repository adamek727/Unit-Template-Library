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
    using MagneticFluxDensityUnit = DivBaseUnits<T, MagneticFlux<T>, Area<T>>;

    template<typename T>
    class MagneticFluxDensity : public MagneticFluxDensityUnit<T> {
    public:
        explicit MagneticFluxDensity(T illuminance) : MagneticFluxDensityUnit<T>{illuminance} {}

        explicit MagneticFluxDensity(const MagneticFlux<T> &mf, const Area<T> &a) : MagneticFluxDensityUnit<T>{
                mf.Wb() / a.m2()} {}

        [[nodiscard]] auto Tesla() const -> T { return this->value(); }

        auto operator+(const MagneticFluxDensity &other) const -> MagneticFluxDensity {
            return MagneticFluxDensity(Tesla() + other.Tesla());
        }

        auto operator-(const MagneticFluxDensity &other) const -> MagneticFluxDensity {
            return MagneticFluxDensity(Tesla() - other.Tesla());
        }

        auto operator*(T scalar) const -> MagneticFluxDensity {
            return MagneticFluxDensity(Tesla() * scalar);
        }

        auto operator/(T scalar) const -> MagneticFluxDensity {
            return MagneticFluxDensity(Tesla() / scalar);
        }

        auto operator*(const Area<T> &other) const -> MagneticFlux<T> {
            return MagneticFlux<T>(Tesla() * other.m2());
        }

        friend auto operator*(T lhs, const MagneticFluxDensity<T>& rhs) -> MagneticFluxDensity<T> {
            return MagneticFluxDensity<T>(rhs.Tesla() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<MagneticFluxDensityUnit<T>> {
        using type = MagneticFluxDensity<T>;
    };
}