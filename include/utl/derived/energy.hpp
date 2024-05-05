/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"
#include "utl/derived/force.hpp"

namespace utl {

    template<typename T>
    using EnergyUnit = MulBaseUnits<T, Force<T>, Length<T>>;

    template<typename T>
    class Energy : public EnergyUnit<T> {

        static constexpr double JOULES_IN_KILOWATHOUR = 3600000.0;
        static constexpr double EVS_IN_JOULE = 6.241509e18;

    public:
        explicit Energy(T energy) : EnergyUnit<T>{energy} {}

        explicit Energy(const Force<T> &f, const Length<T> &l) : EnergyUnit<T>{f.N() * l.m()} {}

        [[nodiscard]] auto kJ() const -> T { return J() / KILO; }

        [[nodiscard]] auto J() const -> T { return this->value(); }

        [[nodiscard]] auto mJ() const -> T { return J() / MILLI; }

        [[nodiscard]] auto kWh() const -> T { return J() / JOULES_IN_KILOWATHOUR; }

        [[nodiscard]] auto eV() const -> T { return J() * EVS_IN_JOULE; }

        auto operator+(const Energy &other) const -> Energy {
            return Energy(J() + other.J());
        }

        auto operator-(const Energy &other) const -> Energy {
            return Energy(J() - other.J());
        }

        auto operator*(const T scalar) const -> Energy<T> {
            return Energy(J() * scalar);
        }

        auto operator/(const T scalar) const -> Energy<T> {
            return Energy(J() / scalar);
        }


        auto operator/(const Length<T> other) const -> Force<T> {
            return Force<T>(J() / other.m());
        }

        auto operator/(const Force<T> other) const -> Length<T> {
            return Length<T>(J() / other.N());
        }

        friend auto operator*(T lhs, const Energy<T>& rhs) -> Energy {
            return Energy<T>(rhs.J() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<EnergyUnit<T>> {
        using type = Energy<T>;
    };
}