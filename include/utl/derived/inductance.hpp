/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/electric_current.hpp"
#include "utl/derived/magnetic_flux.hpp"

namespace utl {

    template<typename T>
    using InductanceUnit = DivBaseUnits<T, MagneticFlux<T>, ElectricCurrent<T>>;

    template<typename T>
    class Inductance : public InductanceUnit<T> {
    public:
        explicit Inductance(T illuminance) : InductanceUnit<T>{illuminance} {}

        explicit Inductance(const MagneticFlux<T> &mf, const ElectricCurrent<T> &ec) : InductanceUnit<T>{
                mf.Wb() / ec.A()} {}

        [[nodiscard]] auto H() const -> T { return this->value(); }

        auto operator+(const Inductance &other) const -> Inductance {
            return Inductance(H() + other.H());
        }

        auto operator-(const Inductance &other) const -> Inductance {
            return Inductance(H() - other.H());
        }

        auto operator*(T scalar) const -> Inductance {
            return Inductance(H() * scalar);
        }

        auto operator/(T scalar) const -> Inductance {
            return Inductance(H() / scalar);
        }

        auto operator*(const ElectricCurrent<T> &other) const -> MagneticFlux<T> {
            return MagneticFlux<T>(H() * other.A());
        }

        friend auto operator*(T lhs, const Inductance<T>& rhs) -> Inductance<T> {
            return Inductance<T>(rhs.H() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<InductanceUnit<T>> {
        using type = Inductance<T>;
    };
}
