/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <array>
#include "utl/helper.hpp"

namespace utl {

    template<class UnitType>
    struct UnitMapper {
    };

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT>
    class BaseUnit {
        using Self = BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT>;
        using SelfInv = BaseUnit<T, -TIME, -LENGTH, -MASS, -EL_CURR, -TD_TEMP, -AM_OF_SUB, -LUM_INT>;
    public:
        BaseUnit() = default;

        explicit BaseUnit(const T &value) : value_{value} {};

        [[nodiscard]] static constexpr std::array<int8_t, 7> dim() {
            return {TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT};
        }

        static constexpr int8_t TimeDim() { return TIME; };
        static constexpr int8_t LengthDim() { return LENGTH; };
        static constexpr int8_t MassDim() { return MASS; };
        static constexpr int8_t ElCurrDim() { return EL_CURR; };
        static constexpr int8_t TdTempDim() { return TD_TEMP; };
        static constexpr int8_t AmOfSubDim() { return AM_OF_SUB; };
        static constexpr int8_t LumIntDim() { return LUM_INT; };

        inline auto value() const -> const T & {
            return value_;
        }

        void set_value(const T &val) {
            value_ = val;
        }

        auto raw() const -> Self {
            return *this;
        }

        virtual auto inv() const -> SelfInv {
            return SelfInv {
                    static_cast<T>(1.0) / value_
            };
        }

        template<typename UnitType = Self>
        typename UnitMapper<UnitType>::type type() const {
            return typename UnitMapper<UnitType>::type(this->value_);
        }

        auto operator+(const BaseUnit &other) -> BaseUnit {
            return BaseUnit(value_ + other.value_);
        }

        auto operator-(const BaseUnit &other) -> BaseUnit {
            return BaseUnit(value_ - other.value_);
        }

        auto operator*(T scalar) const -> Self {
            return Self(value() * scalar);
        }

        auto operator/(T scalar) const -> Self {
            return Self(value() / scalar);
        }

        friend auto operator*(T lhs, const Self& rhs) -> Self {
            return Self(rhs.value() * lhs);
        }

        template<int8_t TIME_O, int8_t LENGTH_O, int8_t MASS_O, int8_t EL_CURR_O, int8_t TD_TEMP_O, int8_t AM_OF_SUB_O, int8_t LUM_INT_O>
        auto operator*(
                const BaseUnit<T, TIME_O, LENGTH_O, MASS_O, EL_CURR_O, TD_TEMP_O, AM_OF_SUB_O, LUM_INT_O> &other) -> BaseUnit<T,
                TIME + TIME_O,
                LENGTH + LENGTH_O,
                MASS + MASS_O,
                EL_CURR + EL_CURR_O,
                TD_TEMP + TD_TEMP_O,
                AM_OF_SUB + AM_OF_SUB_O,
                LUM_INT + LUM_INT_O> {
            return BaseUnit<T,
                    TIME + TIME_O,
                    LENGTH + LENGTH_O,
                    MASS + MASS_O,
                    EL_CURR + EL_CURR_O,
                    TD_TEMP + TD_TEMP_O,
                    AM_OF_SUB + AM_OF_SUB_O,
                    LUM_INT + LUM_INT_O>(
                    value_ * other.value());
        }

        template<int8_t TIME_O, int8_t LENGTH_O, int8_t MASS_O, int8_t EL_CURR_O, int8_t TD_TEMP_O, int8_t AM_OF_SUB_O, int8_t LUM_INT_O>
        auto operator/(
                const BaseUnit<T, TIME_O, LENGTH_O, MASS_O, EL_CURR_O, TD_TEMP_O, AM_OF_SUB_O, LUM_INT_O> &other) -> BaseUnit<T,
                TIME - TIME_O,
                LENGTH - LENGTH_O,
                MASS - MASS_O,
                EL_CURR - EL_CURR_O,
                TD_TEMP - TD_TEMP_O,
                AM_OF_SUB - AM_OF_SUB_O,
                LUM_INT - LUM_INT_O> {
            return BaseUnit<T,
                    TIME - TIME_O,
                    LENGTH - LENGTH_O,
                    MASS - MASS_O,
                    EL_CURR - EL_CURR_O,
                    TD_TEMP - TD_TEMP_O,
                    AM_OF_SUB - AM_OF_SUB_O,
                    LUM_INT - LUM_INT_O>(
                    value_ / other.value());
        }

    private:
        T value_ = 0;
    };

    template<typename T>
    using Unit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 0>;

    template<typename T, typename U1, typename U2>
    using MulBaseUnits = BaseUnit<T,
            U1::TimeDim() + U2::TimeDim(),
            U1::LengthDim() + U2::LengthDim(),
            U1::MassDim() + U2::MassDim(),
            U1::ElCurrDim() + U2::ElCurrDim(),
            U1::TdTempDim() + U2::TdTempDim(),
            U1::AmOfSubDim() + U2::AmOfSubDim(),
            U1::LumIntDim() + U2::LumIntDim()>;

    template<typename T, typename U1, typename U2>
    using DivBaseUnits = BaseUnit<T,
            U1::TimeDim() - U2::TimeDim(),
            U1::LengthDim() - U2::LengthDim(),
            U1::MassDim() - U2::MassDim(),
            U1::ElCurrDim() - U2::ElCurrDim(),
            U1::TdTempDim() - U2::TdTempDim(),
            U1::AmOfSubDim() - U2::AmOfSubDim(),
            U1::LumIntDim() - U2::LumIntDim()>;

    template<typename T, typename U1>
    using InvBaseUnit = BaseUnit<T,
            -U1::TimeDim(),
            -U1::LengthDim(),
            -U1::MassDim(),
            -U1::ElCurrDim(),
            -U1::TdTempDim(),
            -U1::AmOfSubDim(),
            -U1::LumIntDim()>;
}
