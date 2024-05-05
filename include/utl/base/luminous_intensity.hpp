/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using LuminousIntensityUnit = BaseUnit<T, 0, 0, 0, 0, 0, 0, 1>;

    template<typename T>
    class LuminousIntensity : public LuminousIntensityUnit<T> {
    public:
        explicit LuminousIntensity(T luminous_intensity) : LuminousIntensityUnit<T>{
                luminous_intensity} {}

        [[nodiscard]] auto cd() const -> T { return this->value(); }

        auto operator+(const LuminousIntensity &other) const -> LuminousIntensity {
            return LuminousIntensity(cd() + other.cd());
        }

        auto operator-(const LuminousIntensity &other) const -> LuminousIntensity {
            return LuminousIntensity(cd() - other.cd());
        }

        auto operator*(T scalar) const -> LuminousIntensity {
            return LuminousIntensity(cd() * scalar);
        }

        auto operator/(T scalar) const -> LuminousIntensity {
            return LuminousIntensity(cd() / scalar);
        }

        friend auto operator*(T lhs, const LuminousIntensity<T>& rhs) -> LuminousIntensity<T> {
            return LuminousIntensity<T>(rhs.cd() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<LuminousIntensityUnit<T>> {
        using type = LuminousIntensity<T>;
    };
}