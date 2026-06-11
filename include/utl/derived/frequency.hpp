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
        explicit Frequency(T freq) : FrequencyUnit<T>{freq} {}

        [[nodiscard]] auto THz() const -> T { return Hz() / TERA; }

        [[nodiscard]] auto GHz() const -> T { return Hz() / GIGA; }

        [[nodiscard]] auto MHz() const -> T { return Hz() / MEGA; }

        [[nodiscard]] auto kHz() const -> T { return Hz() / KILO; }

        [[nodiscard]] auto Hz() const -> T { return this->value(); }

    };

    template<typename T>
    struct UnitMapper<FrequencyUnit<T>> {
        using type = Frequency<T>;
    };
}