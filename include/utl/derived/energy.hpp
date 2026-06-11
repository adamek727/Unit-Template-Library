/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"
#include "utl/derived/force.hpp"

namespace utl {

    template<typename T>
    using EnergyUnit = BaseUnit<T, -2, 2, 1, 0, 0, 0, 0>;

    template<typename T>
    class Energy : public EnergyUnit<T> {

        static constexpr double JOULES_IN_KILOWATHOUR = 3600000.0;
        static constexpr double EVS_IN_JOULE = 6.241509e18;
        static constexpr double JOULES_IN_WATTHOUR = 3600.0;
        static constexpr double JOULES_IN_CALORIE = 4.184;

    public:
        constexpr Energy() = default;

        constexpr explicit Energy(T energy) : EnergyUnit<T>{energy} {}

        constexpr explicit Energy(const Force<T> &f, const Length<T> &l) : EnergyUnit<T>{f.N() * l.m()} {}

        [[nodiscard]] constexpr auto kJ() const -> T { return static_cast<T>(J() / KILO); }

        [[nodiscard]] constexpr auto J() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto mJ() const -> T { return static_cast<T>(J() / MILLI); }

        [[nodiscard]] constexpr auto kWh() const -> T { return static_cast<T>(J() / JOULES_IN_KILOWATHOUR); }

        [[nodiscard]] constexpr auto eV() const -> T { return static_cast<T>(J() * EVS_IN_JOULE); }

        [[nodiscard]] constexpr auto Wh() const -> T { return static_cast<T>(J() / JOULES_IN_WATTHOUR); }

        [[nodiscard]] constexpr auto cal() const -> T { return static_cast<T>(J() / JOULES_IN_CALORIE); }

    };

    template<typename T>
    struct UnitMapper<EnergyUnit<T>> {
        using type = Energy<T>;
    };
}