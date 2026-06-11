/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/length.hpp"

namespace utl {

    template<typename T>
    using AreaUnit = BaseUnit<T, 0, 2, 0, 0, 0, 0, 0>;

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

    };

    template<typename T>
    struct UnitMapper<AreaUnit<T>> {
        using type = Area<T>;
    };
}
