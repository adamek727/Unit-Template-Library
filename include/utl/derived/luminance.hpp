/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/luminous_intensity.hpp"
#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using LuminanceUnit = BaseUnit<T, 0, -2, 0, 0, 0, 0, 1>;

    template<typename T>
    class Luminance : public LuminanceUnit<T> {

    public:
        constexpr explicit Luminance(T luminance) : LuminanceUnit<T>{luminance} {}

        constexpr explicit Luminance(const LuminousIntensity<T> &i, const Area<T> &a) : LuminanceUnit<T>{i.cd() / a.m2()} {}

        [[nodiscard]] constexpr auto cdpm2() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<LuminanceUnit<T>> {
        using type = Luminance<T>;
    };
} // namespace utl
