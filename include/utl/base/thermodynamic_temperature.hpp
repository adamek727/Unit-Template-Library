/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using ThermodynamicTemperatureUnit = BaseUnit<T, 0, 0, 0, 0, 1, 0, 0>;

    template<typename T>
    class ThermodynamicTemperature : public ThermodynamicTemperatureUnit<T> {

        static constexpr double K2C = -273.15;
        static constexpr double C2F_K = 1.8;
        static constexpr double C2F_Q = 32;

    public:

        enum class TYPE {
            KELVIN,
            CELSIUS,
            FAHRENHEIT,
        };

        constexpr explicit ThermodynamicTemperature(T thermodyn_temp, const TYPE &type = TYPE::KELVIN) {
            switch (type) {
                case TYPE::CELSIUS:
                    this->set_value(thermodyn_temp - K2C);
                    break;
                case TYPE::FAHRENHEIT:
                    this->set_value((thermodyn_temp - C2F_Q) / C2F_K);
                    break;
                default:
                    this->set_value(thermodyn_temp);
                    break;
            }
        }

        [[nodiscard]] constexpr auto K() const -> T { return this->value(); }

        [[nodiscard]] constexpr auto degC() const -> T { return K() + K2C; }

        [[nodiscard]] constexpr auto degF() const -> T { return degC() * C2F_K + C2F_Q; }

    };

    template<typename T>
    struct UnitMapper<ThermodynamicTemperatureUnit<T>> {
        using type = ThermodynamicTemperature<T>;
    };
}