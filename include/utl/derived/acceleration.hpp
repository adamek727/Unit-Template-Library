/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/all.hpp"
#include "utl/derived/velocity.hpp"

namespace utl {

    template<typename T>
    using AccelerationUnit = BaseUnit<T, -2, 1, 0, 0, 0, 0, 0>;

    template<typename T>
    class Acceleration : public AccelerationUnit<T> {

    public:
        constexpr explicit Acceleration(T acc) : AccelerationUnit<T>{acc} {}

        constexpr explicit Acceleration(const Velocity<T> v, const Time<T> t) : AccelerationUnit<T>{v.mps() / t.s()} {}

        [[nodiscard]] constexpr auto mps2() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<AccelerationUnit<T>> {
        using type = Acceleration<T>;
    };
}