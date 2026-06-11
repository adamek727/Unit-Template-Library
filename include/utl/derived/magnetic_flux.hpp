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
    using MagneticFluxUnit = BaseUnit<T, -2, 2, 1, -1, 0, 0, 0>;

    template<typename T>
    class MagneticFlux : public MagneticFluxUnit<T> {
    public:
        explicit MagneticFlux(T illuminance) : MagneticFluxUnit<T>{illuminance} {}

        explicit MagneticFlux(const Voltage<T> &v, const Time<T> &t) : MagneticFluxUnit<T>{
                v.V() * t.s()} {}

        explicit MagneticFlux(const MagneticFluxDensity<T> &mfd, const Area<T> &a) : MagneticFluxUnit<T>{
                mfd.Tesla() * a.m2()} {}

        [[nodiscard]] auto Wb() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<MagneticFluxUnit<T>> {
        using type = MagneticFlux<T>;
    };
}