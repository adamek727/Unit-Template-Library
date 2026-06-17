/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/mass.hpp"
#include "utl/derived/volume.hpp"

namespace utl {

    template<typename T>
    using DensityUnit = BaseUnit<T, 0, -3, 1, 0, 0, 0, 0>;

    template<typename T>
    class Density : public DensityUnit<T> {

    public:
        constexpr explicit Density(T density) : DensityUnit<T>{density} {}

        constexpr explicit Density(const Mass<T> &m, const Volume<T> &v) : DensityUnit<T>{m.kg() / v.m3()} {}

        [[nodiscard]] constexpr auto kgpm3() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<DensityUnit<T>> {
        using type = Density<T>;
    };
} // namespace utl
