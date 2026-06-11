/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/luminous_flux.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using IlluminanceUnit = BaseUnit<T, 0, -2, 0, 0, 0, 0, 1>;

    template<typename T>
    class Illuminance : public IlluminanceUnit<T> {
    public:
        constexpr Illuminance() = default;

        constexpr explicit Illuminance(T illuminance) : IlluminanceUnit<T>{
                illuminance} {}

        constexpr explicit Illuminance(const LuminousFlux<T> &lf, const Area<T> &a) : IlluminanceUnit<T>{
                lf.lm() / a.m2()} {}

        [[nodiscard]] constexpr auto lux() const -> T { return static_cast<T>(this->value()); }

        using IlluminanceUnit<T>::operator*;

        constexpr auto operator*(const Area<T> &other) const -> LuminousFlux<T> {
            return LuminousFlux<T>(lux() * other.m2());
        }
    };

    template<typename T>
    struct UnitMapper<IlluminanceUnit<T>> {
        using type = Illuminance<T>;
    };
}