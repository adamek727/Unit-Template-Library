/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/luminous_flux.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using IlluminanceUnit = DivBaseUnits<T, LuminousFlux<T>, Area<T>>;

    template<typename T>
    class Illuminance : public IlluminanceUnit<T> {
    public:
        explicit Illuminance(T illuminance) : IlluminanceUnit<T>{
                illuminance} {}

        explicit Illuminance(const LuminousFlux<T> &lf, const Area<T> &a) : IlluminanceUnit<T>{
                lf.lm() / a.m2()} {}

        [[nodiscard]] auto lux() const -> T { return this->value(); }

        auto operator+(const Illuminance &other) const -> Illuminance {
            return Illuminance(lux() + other.lux());
        }

        auto operator-(const Illuminance &other) const -> Illuminance {
            return Illuminance(lux() - other.lux());
        }

        auto operator*(T scalar) const -> Illuminance {
            return Illuminance(lux() * scalar);
        }

        auto operator/(T scalar) const -> Illuminance {
            return Illuminance(lux() / scalar);
        }

        auto operator*(const Area<T> &other) const -> LuminousFlux<T> {
            return LuminousFlux<T>(lux() * other.m2());
        }

        friend auto operator*(T lhs, const Illuminance<T>& rhs) -> Illuminance<T> {
            return Illuminance<T>(rhs.lux() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<IlluminanceUnit<T>> {
        using type = Illuminance<T>;
    };
}