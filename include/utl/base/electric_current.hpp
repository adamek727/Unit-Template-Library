/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using ElectricCurrentUnit = BaseUnit<T, 0, 0, 0, 1, 0, 0, 0>;

    template<typename T>
    class ElectricCurrent : public ElectricCurrentUnit<T> {
    public:
        explicit ElectricCurrent(T current) : ElectricCurrentUnit<T>{current} {}

        [[nodiscard]] auto kA() const -> T { return A() / KILO; }

        [[nodiscard]] auto A() const -> T { return this->value(); }

        [[nodiscard]] auto mA() const -> T { return static_cast<T>(A() / MILLI ); }

        [[nodiscard]] auto uA() const -> T { return static_cast<T>(A() / MICRO); }

        [[nodiscard]] auto nA() const -> T { return static_cast<T>(A() / NANO); }

        auto operator+(const ElectricCurrent &other) const -> ElectricCurrent {
            return ElectricCurrent(A() + other.A());
        }

        auto operator-(const ElectricCurrent &other) const -> ElectricCurrent {
            return ElectricCurrent(A() - other.A());
        }

        auto operator*(T scalar) const -> ElectricCurrent {
            return ElectricCurrent(A() * scalar);
        }

        auto operator/(T scalar) const -> ElectricCurrent {
            return ElectricCurrent(A() / scalar);
        }

        friend auto operator*(T lhs, const ElectricCurrent<T>& rhs) -> ElectricCurrent<T> {
            return ElectricCurrent<T>(rhs.A() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<ElectricCurrentUnit<T>> {
        using type = ElectricCurrent<T>;
    };
}
