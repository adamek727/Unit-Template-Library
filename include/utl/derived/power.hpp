/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"
#include "utl/derived/energy.hpp"
#include "utl/derived/frequency.hpp"

namespace utl {


    template<typename T>
    using PowerUnit = DivBaseUnits<T, Energy<T>, Time<T>>;

    template<typename T>
    class Power : public PowerUnit<T> {

    public:
        explicit Power(T power) : PowerUnit<T>{power} {}

        explicit Power(const Energy<T> &e, const Time<T> &t) : PowerUnit<T>{e.J() / t.s()} {}

        [[nodiscard]] auto kW() const -> T { return W() / KILO; }

        [[nodiscard]] auto W() const -> T { return this->value(); }

        auto operator+(const Power &other) const -> Power {
            return Power(W() + other.W());
        }

        auto operator-(const Power &other) const -> Power {
            return Power(W() - other.W());
        }

        auto operator*(const T scalar) const -> Power<T> {
            return Power(W() * scalar);
        }

        auto operator/(const T scalar) const -> Power<T> {
            return Power(W() / scalar);
        }


        auto operator*(const Time<T> &other) const -> Energy<T> {
            return Energy<T>(W() * other.s());
        }

        auto operator/(const Energy<T> other) const -> Frequency<T> {
            return Frequency<T>(W() / other.J());
        }

        friend auto operator*(T lhs, const Power<T>& rhs) -> Power<T> {
            return Power<T>(rhs.W() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<PowerUnit<T>> {
        using type = Power<T>;
    };
}