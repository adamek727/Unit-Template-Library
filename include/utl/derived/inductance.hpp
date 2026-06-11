/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/derived/magnetic_flux.hpp"

namespace utl {

    template<typename T>
    using InductanceUnit = BaseUnit<T, -2, 2, 1, -2, 0, 0, 0>;

    template<typename T>
    class Inductance : public InductanceUnit<T> {
    public:
        explicit Inductance(T illuminance) : InductanceUnit<T>{illuminance} {}

        explicit Inductance(const MagneticFlux<T> &mf, const ElectricCurrent<T> &ec) : InductanceUnit<T>{
                mf.Wb() / ec.A()} {}

        [[nodiscard]] auto H() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<InductanceUnit<T>> {
        using type = Inductance<T>;
    };
}
