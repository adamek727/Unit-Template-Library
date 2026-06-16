/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/base_unit.hpp"

namespace utl {

    template<typename T>
    using TorqueUnit = BaseUnit<T, -2, 2, 1, 0, 0, 0, 0, -1>;

    template<typename T>
    class Torque : public TorqueUnit<T> {
    public:
        constexpr explicit Torque(T torque) : TorqueUnit<T>{torque} {}

        [[nodiscard]] constexpr auto Nm() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<TorqueUnit<T>> {
        using type = Torque<T>;
    };
} // namespace utl
