/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/mass.hpp"
#include "utl/derived/energy.hpp"

namespace utl {

    template<typename T>
    using AbsorbedDoseUnit = BaseUnit<T, -2, 2, 0, 0, 0, 0, 0>;

    template<typename T>
    class AbsorbedDose : public AbsorbedDoseUnit<T> {

    public:
        explicit AbsorbedDose(T abs_dose) : AbsorbedDoseUnit<T>{abs_dose} {}

        explicit AbsorbedDose(const Energy<T>& e, const Mass<T>& m) : AbsorbedDoseUnit<T>{e.J() / m.kg()} {}

        [[nodiscard]] auto Gy() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<AbsorbedDoseUnit<T>> {
        using type = AbsorbedDose<T>;
    };
}