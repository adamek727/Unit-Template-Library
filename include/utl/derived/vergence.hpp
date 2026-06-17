/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"

namespace utl {

    template<typename T>
    using VergenceUnit = BaseUnit<T, 0, -1, 0, 0, 0, 0, 0>;

    template<typename T>
    class Vergence : public VergenceUnit<T> {

    public:
        constexpr explicit Vergence(T vergence) : VergenceUnit<T>{vergence} {}

        constexpr explicit Vergence(const Length<T> focal_length) : VergenceUnit<T>{static_cast<T>(1.0) / focal_length.m()} {}

        [[nodiscard]] constexpr auto dpt() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<VergenceUnit<T>> {
        using type = Vergence<T>;
    };
} // namespace utl
