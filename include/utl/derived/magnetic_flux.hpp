/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"
#include "utl/derived/area.hpp"
#include "utl/derived/voltage.hpp"

namespace utl {


    template<typename T>
    class MagneticFluxDensity;

    template<typename T>
    using MagneticFluxUnit = MulBaseUnits<T, Voltage<T>, Time<T>>;

    template<typename T>
    class MagneticFlux : public MagneticFluxUnit<T> {
    public:
        explicit MagneticFlux(T illuminance) : MagneticFluxUnit<T>{illuminance} {}

        explicit MagneticFlux(const Voltage<T> &v, const Time<T> &t) : MagneticFluxUnit<T>{
                v.V() * t.s()} {}

        explicit MagneticFlux(const MagneticFluxDensity<T> &mfd, const Area<T> &a) : MagneticFluxUnit<T>{
                mfd.Tesla() * a.m2()} {}

        [[nodiscard]] auto Wb() const -> T { return this->value(); }

        auto operator+(const MagneticFlux &other) const -> MagneticFlux {
            return MagneticFlux(Wb() + other.Wb());
        }

        auto operator-(const MagneticFlux &other) const -> MagneticFlux {
            return MagneticFlux(Wb() - other.Wb());
        }

        auto operator*(T scalar) const -> MagneticFlux {
            return MagneticFlux(Wb() * scalar);
        }

        auto operator/(T scalar) const -> MagneticFlux {
            return MagneticFlux(Wb() / scalar);
        }

        auto operator/(const Voltage<T> &other) const -> Time<T> {
            return Time<T>(Wb() / other.V());
        }

        auto operator/(const Time<T> &other) const -> Voltage<T> {
            return Voltage<T>(Wb() / other.s());
        }

        friend auto operator*(T lhs, const MagneticFlux<T>& rhs) -> MagneticFlux<T> {
            return MagneticFlux<T>(rhs.Wb() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<MagneticFluxUnit<T>> {
        using type = MagneticFlux<T>;
    };
}