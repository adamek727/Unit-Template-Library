/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <array>
#include <cstdint>
#include <type_traits>
#include "utl/helper.hpp"

namespace utl {

    template<class UnitType>
    struct UnitMapper {
    };

    template<class UnitType, class = void>
    struct MappedUnit {
        using type = UnitType;
    };

    template<class UnitType>
    struct MappedUnit<UnitType, std::void_t<typename UnitMapper<UnitType>::type>> {
        using type = typename UnitMapper<UnitType>::type;
    };

    template<class UnitType>
    using mapped_unit_t = typename MappedUnit<UnitType>::type;

    template<typename T, int8_t TIME, int8_t LENGTH, int8_t MASS, int8_t EL_CURR, int8_t TD_TEMP, int8_t AM_OF_SUB, int8_t LUM_INT, int8_t ANGLE = 0>
    class BaseUnit {
        using Self = BaseUnit<T, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE>;
        using SelfInv = BaseUnit<T, -TIME, -LENGTH, -MASS, -EL_CURR, -TD_TEMP, -AM_OF_SUB, -LUM_INT, -ANGLE>;
    public:
        BaseUnit() = delete;

        constexpr explicit BaseUnit(const T &value) : value_{value} {};

        [[nodiscard]] static constexpr std::array<int8_t, 8> dim() {
            return {TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE};
        }

        static constexpr int8_t TimeDim() { return TIME; };
        static constexpr int8_t LengthDim() { return LENGTH; };
        static constexpr int8_t MassDim() { return MASS; };
        static constexpr int8_t ElCurrDim() { return EL_CURR; };
        static constexpr int8_t TdTempDim() { return TD_TEMP; };
        static constexpr int8_t AmOfSubDim() { return AM_OF_SUB; };
        static constexpr int8_t LumIntDim() { return LUM_INT; };
        static constexpr int8_t AngleDim() { return ANGLE; };

        constexpr auto value() const -> const T & {
            return value_;
        }

        constexpr void set_value(const T &val) {
            value_ = val;
        }

        constexpr auto raw() const -> Self {
            return *this;
        }

        constexpr auto inv() const -> SelfInv {
            return SelfInv{
                static_cast<T>(1.0) / value_};
        }

        template<typename UnitType = Self>
        constexpr typename UnitMapper<UnitType>::type type() const {
            return typename UnitMapper<UnitType>::type(this->value_);
        }

        template<typename U>
        constexpr auto operator+(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> mapped_unit_t<BaseUnit<std::common_type_t<T, U>, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE>> {
            using Result = mapped_unit_t<BaseUnit<std::common_type_t<T, U>, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE>>;
            return Result(value_ + other.value());
        }

        template<typename U>
        constexpr auto operator-(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> mapped_unit_t<BaseUnit<std::common_type_t<T, U>, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE>> {
            using Result = mapped_unit_t<BaseUnit<std::common_type_t<T, U>, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE>>;
            return Result(value_ - other.value());
        }

        constexpr auto operator*(T scalar) const -> mapped_unit_t<Self> {
            return mapped_unit_t<Self>(value() * scalar);
        }

        constexpr auto operator/(T scalar) const -> mapped_unit_t<Self> {
            return mapped_unit_t<Self>(value() / scalar);
        }

        friend constexpr auto operator*(T lhs, const Self &rhs) -> mapped_unit_t<Self> {
            return mapped_unit_t<Self>(rhs.value() * lhs);
        }

        constexpr auto operator-() const -> mapped_unit_t<Self> {
            return mapped_unit_t<Self>(-value_);
        }

        constexpr auto operator+=(const BaseUnit &other) -> BaseUnit & {
            value_ += other.value_;
            return *this;
        }

        constexpr auto operator-=(const BaseUnit &other) -> BaseUnit & {
            value_ -= other.value_;
            return *this;
        }

        constexpr auto operator*=(T scalar) -> BaseUnit & {
            value_ *= scalar;
            return *this;
        }

        constexpr auto operator/=(T scalar) -> BaseUnit & {
            value_ /= scalar;
            return *this;
        }

        template<typename U>
        constexpr auto operator==(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> bool { return value_ == other.value(); }

        template<typename U>
        constexpr auto operator!=(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> bool { return value_ != other.value(); }

        template<typename U>
        constexpr auto operator<(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> bool { return value_ < other.value(); }

        template<typename U>
        constexpr auto operator<=(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> bool { return value_ <= other.value(); }

        template<typename U>
        constexpr auto operator>(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> bool { return value_ > other.value(); }

        template<typename U>
        constexpr auto operator>=(const BaseUnit<U, TIME, LENGTH, MASS, EL_CURR, TD_TEMP, AM_OF_SUB, LUM_INT, ANGLE> &other) const -> bool { return value_ >= other.value(); }

    private:
        T value_;
    };

    template<typename T>
    using Unit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 0, 0>;

    template<typename T, typename U1, typename U2>
    using MulBaseUnits = BaseUnit<T,
                                  U1::TimeDim() + U2::TimeDim(),
                                  U1::LengthDim() + U2::LengthDim(),
                                  U1::MassDim() + U2::MassDim(),
                                  U1::ElCurrDim() + U2::ElCurrDim(),
                                  U1::TdTempDim() + U2::TdTempDim(),
                                  U1::AmOfSubDim() + U2::AmOfSubDim(),
                                  U1::LumIntDim() + U2::LumIntDim(),
                                  U1::AngleDim() + U2::AngleDim()>;

    template<typename T, typename U1, typename U2>
    using DivBaseUnits = BaseUnit<T,
                                  U1::TimeDim() - U2::TimeDim(),
                                  U1::LengthDim() - U2::LengthDim(),
                                  U1::MassDim() - U2::MassDim(),
                                  U1::ElCurrDim() - U2::ElCurrDim(),
                                  U1::TdTempDim() - U2::TdTempDim(),
                                  U1::AmOfSubDim() - U2::AmOfSubDim(),
                                  U1::LumIntDim() - U2::LumIntDim(),
                                  U1::AngleDim() - U2::AngleDim()>;

    template<typename T, typename U1>
    using InvBaseUnit = BaseUnit<T,
                                 -U1::TimeDim(),
                                 -U1::LengthDim(),
                                 -U1::MassDim(),
                                 -U1::ElCurrDim(),
                                 -U1::TdTempDim(),
                                 -U1::AmOfSubDim(),
                                 -U1::LumIntDim(),
                                 -U1::AngleDim()>;
} // namespace utl
