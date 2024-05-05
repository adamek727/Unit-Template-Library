/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/mass.hpp"
#include "utl/derived/energy.hpp"

namespace utl {

    template<typename T>
    using AbsorbedDoseUnit = DivBaseUnits<T, Energy<T>, Mass<T>>;

    template<typename T>
    class AbsorbedDose : public AbsorbedDoseUnit<T> {

    public:
        explicit AbsorbedDose(T abs_dose) : AbsorbedDoseUnit<T>{abs_dose} {}

        explicit AbsorbedDose(const Energy<T>& e, const Mass<T>& m) : AbsorbedDoseUnit<T>{e.J() / m.kg()} {}

        [[nodiscard]] auto Gy() const -> T { return this->value(); }

        auto operator+(const AbsorbedDose &other) const -> AbsorbedDose {
            return AbsorbedDose(Gy() + other.Gy());
        }

        auto operator-(const AbsorbedDose &other) const -> AbsorbedDose {
            return AbsorbedDose(Gy() - other.Gy());
        }

        auto operator*(T scalar) const -> AbsorbedDose {
            return AbsorbedDose(Gy() * scalar);
        }

        auto operator/(T scalar) const -> AbsorbedDose {
            return AbsorbedDose(Gy() / scalar);
        }

        auto operator*(const Mass<T> &other) const -> Energy<T> {
            return Energy(Gy() * other.kg());
        }
    };

    template<typename T>
    struct UnitMapper<AbsorbedDoseUnit<T>> {
        using type = AbsorbedDose<T>;
    };
}