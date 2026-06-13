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

    private:
        static constexpr auto to_kelvin(T thermodyn_temp, const TYPE &type) -> T {
            switch (type) {
                case TYPE::CELSIUS:
                    return static_cast<T>(thermodyn_temp - K2C);
                case TYPE::FAHRENHEIT:
                    return static_cast<T>((thermodyn_temp - C2F_Q) / C2F_K);
                default:
                    return thermodyn_temp;
            }
        }

    public:
        constexpr explicit ThermodynamicTemperature(T thermodyn_temp, const TYPE &type = TYPE::KELVIN)
            : ThermodynamicTemperatureUnit<T>{to_kelvin(thermodyn_temp, type)} {}

        [[nodiscard]] constexpr auto K() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto degC() const -> T { return static_cast<T>(K() + K2C); }

        [[nodiscard]] constexpr auto degF() const -> T { return static_cast<T>(degC() * C2F_K + C2F_Q); }
    };

    template<typename T>
    struct UnitMapper<ThermodynamicTemperatureUnit<T>> {
        using type = ThermodynamicTemperature<T>;
    };
} // namespace utl