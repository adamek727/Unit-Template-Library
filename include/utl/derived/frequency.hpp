/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    using FrequencyUnit = BaseUnit<T, -1, 0, 0, 0, 0, 0, 0>;

    template<typename T>
    class Frequency : public FrequencyUnit<T> {

    public:
        constexpr explicit Frequency(T freq) : FrequencyUnit<T>{freq} {}

        [[nodiscard]] constexpr auto THz() const -> T { return static_cast<T>(Hz() / TERA); }

        [[nodiscard]] constexpr auto GHz() const -> T { return static_cast<T>(Hz() / GIGA); }

        [[nodiscard]] constexpr auto MHz() const -> T { return static_cast<T>(Hz() / MEGA); }

        [[nodiscard]] constexpr auto kHz() const -> T { return static_cast<T>(Hz() / KILO); }

        [[nodiscard]] constexpr auto Hz() const -> T { return static_cast<T>(this->value()); }
    };

    template<typename T>
    struct UnitMapper<FrequencyUnit<T>> {
        using type = Frequency<T>;
    };
} // namespace utl