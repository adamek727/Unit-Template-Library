/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"

namespace utl {

    template<typename T>
    class Volume;


    template<typename T>
    using AreaUnit = MulBaseUnits<T, Length<T>, Length<T>>;

    template<typename T>
    class Area : public AreaUnit<T> {

    public:
        explicit Area(T area) : AreaUnit<T>{area} {}

        explicit Area(const Length<T> l1, const Length<T> l2) : AreaUnit<T>{l1.m() * l2.m()} {}

        [[nodiscard]] auto km2() const -> T { return m2() / KILO / KILO; }

        [[nodiscard]] auto ha() const -> T { return a() / HECTO; }

        [[nodiscard]] auto a() const -> T { return m2() / HECTO; }

        [[nodiscard]] auto m2() const -> T { return this->value(); }

        [[nodiscard]] auto mm2() const -> T { return m2() / MILLI / MILLI; }

        [[nodiscard]] auto um2() const -> T { return m2() / MICRO / MICRO; }

        [[nodiscard]] auto nm2() const -> T { return m2() / NANO / NANO; }

        auto operator+(const Area &other) const -> Area {
            return Area(m2() + other.m2());
        }

        auto operator-(const Area &other) const -> Area {
            return Area(m2() - other.m2());
        }

        auto operator*(T scalar) const -> Area {
            return Area(m2() * scalar);
        }

        auto operator/(T scalar) const -> Area {
            return Area(m2() / scalar);
        }

        auto operator*(const Length<T> &other) const -> Volume<T> {
            return Volume<T>(m2() * other.m());
        }

        auto operator/(const Length<T> &other) const -> Length<T> {
            return Length<T>(m2() / other.m());
        }

        friend auto operator*(const T lhs, const Area& rhs) -> Area<T> {
            return Area<T>(rhs.m2() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<AreaUnit<T>> {
        using type = Area<T>;
    };
}
