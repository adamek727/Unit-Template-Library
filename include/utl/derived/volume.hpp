/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"
#include "utl/derived/area.hpp"

namespace utl {
    template<typename T>
    using VolumeUnit = BaseUnit<T, 0, 3, 0, 0, 0, 0, 0>;

    template<typename T>
    class Volume : public VolumeUnit<T> {

        static constexpr double LITERS_IN_M3 = 1000;

    public:
        explicit Volume(T volume) : VolumeUnit<T>{volume} {}

        explicit Volume(const Length<T> l1, const Length<T> l2, const Length<T> l3) : VolumeUnit<T>{
                l1.m() * l2.m() * l3.m()} {}

        explicit Volume(const Area<T> a, const Length<T> l) : VolumeUnit<T>{a.m2() * l.m()} {}

        [[nodiscard]] auto m3() const -> T { return this->value(); }

        [[nodiscard]] auto l() const -> T { return this->value() * LITERS_IN_M3; }

    };

    template<typename T>
    struct UnitMapper<VolumeUnit<T>> {
        using type = Volume<T>;
    };
}