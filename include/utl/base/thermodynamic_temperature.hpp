/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/helper.hpp"
#include "utl/base/base_unit.hpp"

namespace utl {

    static constexpr double TEMPERATURE_K2C = -273.15;
    static constexpr double TEMPERATURE_C2F_K = 1.8;
    static constexpr double TEMPERATURE_C2F_Q = 32;

    template<typename T>
    using TemperatureDeltaUnit = BaseUnit<T, 0, 0, 0, 0, 1, 0, 0>;

    template<typename T>
    class TemperatureDelta : public TemperatureDeltaUnit<T> {

    public:
        constexpr explicit TemperatureDelta(T delta) : TemperatureDeltaUnit<T>{delta} {}

        [[nodiscard]] constexpr auto K() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto degC() const -> T { return K(); }

        [[nodiscard]] constexpr auto degF() const -> T { return static_cast<T>(K() * TEMPERATURE_C2F_K); }

        constexpr auto operator+(const TemperatureDelta &other) const -> TemperatureDelta {
            return TemperatureDelta(K() + other.K());
        }

        constexpr auto operator-(const TemperatureDelta &other) const -> TemperatureDelta {
            return TemperatureDelta(K() - other.K());
        }

        constexpr auto operator-() const -> TemperatureDelta {
            return TemperatureDelta(-K());
        }

        constexpr auto operator*(T scalar) const -> TemperatureDelta {
            return TemperatureDelta(K() * scalar);
        }

        constexpr auto operator/(T scalar) const -> TemperatureDelta {
            return TemperatureDelta(K() / scalar);
        }

        friend constexpr auto operator*(T lhs, const TemperatureDelta<T> &rhs) -> TemperatureDelta<T> {
            return TemperatureDelta<T>(rhs.K() * lhs);
        }
    };

    template<typename T>
    using ThermodynamicTemperatureUnit = BaseUnit<T, 0, 0, 0, 0, 1, 0, 0>;

    template<typename T>
    class ThermodynamicTemperature : public ThermodynamicTemperatureUnit<T> {

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
                    return static_cast<T>(thermodyn_temp - TEMPERATURE_K2C);
                case TYPE::FAHRENHEIT:
                    return static_cast<T>((thermodyn_temp - TEMPERATURE_C2F_Q) / TEMPERATURE_C2F_K);
                default:
                    return thermodyn_temp;
            }
        }

    public:
        constexpr explicit ThermodynamicTemperature(T thermodyn_temp, const TYPE &type = TYPE::KELVIN)
            : ThermodynamicTemperatureUnit<T>{to_kelvin(thermodyn_temp, type)} {}

        [[nodiscard]] constexpr auto K() const -> T { return static_cast<T>(this->value()); }

        [[nodiscard]] constexpr auto degC() const -> T { return static_cast<T>(K() + TEMPERATURE_K2C); }

        [[nodiscard]] constexpr auto degF() const -> T { return static_cast<T>(degC() * TEMPERATURE_C2F_K + TEMPERATURE_C2F_Q); }

        constexpr auto operator-(const ThermodynamicTemperature &other) const -> TemperatureDelta<T> {
            return TemperatureDelta<T>(K() - other.K());
        }

        constexpr auto operator+(const TemperatureDelta<T> &delta) const -> ThermodynamicTemperature {
            return ThermodynamicTemperature(K() + delta.K());
        }

        constexpr auto operator-(const TemperatureDelta<T> &delta) const -> ThermodynamicTemperature {
            return ThermodynamicTemperature(K() - delta.K());
        }

        constexpr auto operator+=(const TemperatureDelta<T> &delta) -> ThermodynamicTemperature & {
            this->set_value(K() + delta.K());
            return *this;
        }

        constexpr auto operator-=(const TemperatureDelta<T> &delta) -> ThermodynamicTemperature & {
            this->set_value(K() - delta.K());
            return *this;
        }

        auto operator+(const ThermodynamicTemperature &other) const -> ThermodynamicTemperature = delete;

        auto operator+=(const ThermodynamicTemperature &other) -> ThermodynamicTemperature & = delete;

        auto operator-=(const ThermodynamicTemperature &other) -> ThermodynamicTemperature & = delete;
    };

    template<typename T>
    constexpr auto operator+(const TemperatureDelta<T> &delta, const ThermodynamicTemperature<T> &temp) -> ThermodynamicTemperature<T> {
        return temp + delta;
    }

    template<typename T>
    struct UnitMapper<ThermodynamicTemperatureUnit<T>> {
        using type = ThermodynamicTemperature<T>;
    };
} // namespace utl
