/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using LuminousIntensityUnit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 1>;

    template<typename T>
    class LuminousIntensity : public LuminousIntensityUnit<T> {
    public:
        constexpr LuminousIntensity() = default;

        constexpr explicit LuminousIntensity(T luminous_intensity) : LuminousIntensityUnit<T>{
                luminous_intensity} {}

        [[nodiscard]] constexpr auto cd() const -> T { return static_cast<T>(this->value()); }

    };

    template<typename T>
    struct UnitMapper<LuminousIntensityUnit<T>> {
        using type = LuminousIntensity<T>;
    };
}