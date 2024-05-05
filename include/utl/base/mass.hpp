/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    class Acceleration;

    template<typename T>
    class Force;

    template<typename T>
    using MassUnit = BaseUnit<T, 0, 0, 1, 0, 0, 0, 0>;

    template<typename T>
    class Mass : public MassUnit<T> {
    public:
        explicit Mass(T mass) : MassUnit<T>{mass} {}

        [[nodiscard]] auto tonne() const -> T { return this->value() / KILO; }

        [[nodiscard]] auto kg() const -> T { return this->value(); }

        [[nodiscard]] auto g() const -> T { return static_cast<T>(this->value() / MILLI ); }

        [[nodiscard]] auto mg() const -> T { return static_cast<T>(this->value() / MICRO); }

        [[nodiscard]] auto ug() const -> T { return static_cast<T>(this->value() / NANO); }

        auto operator+(const Mass &other) const -> Mass {
            return Mass(kg() + other.kg());
        }

        auto operator-(const Mass &other) const -> Mass {
            return Mass(kg() - other.kg());
        }

        auto operator*(T scalar) const -> Mass {
            return Mass(kg() * scalar);
        }

        auto operator/(T scalar) const -> Mass {
            return Mass(kg() / scalar);
        }

        auto operator/(const Acceleration<T> &other) const -> Force<T> {
            return Force<T>(kg() / other.mps2());
        }

        friend auto operator*(T lhs, const Mass<T>& rhs) -> Mass<T> {
            return Mass<T>(rhs.kg() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<MassUnit<T>> {
        using type = Mass<T>;
    };
}
