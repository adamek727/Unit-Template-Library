/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/derived/area.hpp"

namespace utl {

    template<typename T>
    using SolidAngleUnit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 0, 2>;

    template<typename T>
    class SolidAngle : public SolidAngleUnit<T> {
    public:
        constexpr explicit SolidAngle(T solid_angle) : SolidAngleUnit<T>{solid_angle} {}

        constexpr explicit SolidAngle(Area<T> a1, Area<T> a2) : SolidAngleUnit<T>{a1.m2() / a2.m2()} {};

        constexpr explicit SolidAngle(Area<T> a, Length<T> r) : SolidAngleUnit<T>{a.m2() / r.m() / r.m()} {};

        [[nodiscard]] constexpr auto sr() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<SolidAngleUnit<T>> {
        using type = SolidAngle<T>;
    };
} // namespace utl
