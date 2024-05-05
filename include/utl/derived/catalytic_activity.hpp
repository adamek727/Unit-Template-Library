/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/amount_of_substance.hpp"
#include "utl/base/time.hpp"
#include "utl/derived/frequency.hpp"

namespace utl {


    template<typename T>
    using CatalyticActivityUnit = DivBaseUnits<T, AmountOfSubstance<T>, Time<T>>;

    template<typename T>
    class CatalyticActivity : public BaseUnit<T, -1, 0, 0, 0, 0, 1, 0> {
    public:
        explicit CatalyticActivity(T catalytic_activity) : CatalyticActivityUnit<T>{catalytic_activity} {}

        explicit CatalyticActivity(const AmountOfSubstance<T> &aos, const Time<T> &t) : CatalyticActivityUnit<T>{
                aos.mol() / t.s()} {}

        [[nodiscard]] auto katal() const -> T { return this->value(); }

        auto operator+(const CatalyticActivity &other) const -> CatalyticActivity {
            return CatalyticActivity(katal() + other.katal());
        }

        auto operator-(const CatalyticActivity &other) const -> CatalyticActivity {
            return CatalyticActivity(katal() - other.katal());
        }

        auto operator*(T scalar) const -> CatalyticActivity {
            return CatalyticActivity(katal() * scalar);
        }

        auto operator/(T scalar) const -> CatalyticActivity {
            return CatalyticActivity(katal() / scalar);
        }

        auto operator*(const Time<T> &other) -> AmountOfSubstance<T> {
            return AmountOfSubstance<T>(katal() * other.s());
        }

        auto operator/(const AmountOfSubstance<T> &other) -> Frequency<T> {
            return Frequency<T>(katal() / other.mol());
        }

        friend auto operator*(T lhs, const CatalyticActivity<T>& rhs) -> CatalyticActivity<T> {
            return CatalyticActivity<T>(rhs.katal() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<CatalyticActivityUnit<T>> {
        using type = CatalyticActivity<T>;
    };
}