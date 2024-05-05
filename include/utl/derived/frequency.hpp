/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include "utl/base/time.hpp"

namespace utl {

    template<typename T>
    using FrequencyUnit = InvBaseUnit<T, Time<T>>;

    template<typename T>
    class Frequency : public FrequencyUnit<T> {

    public:
        explicit Frequency(T freq) : FrequencyUnit<T>{freq} {}

        [[nodiscard]] auto THz() const -> T { return Hz() / TERA; }

        [[nodiscard]] auto GHz() const -> T { return Hz() / GIGA; }

        [[nodiscard]] auto MHz() const -> T { return Hz() / MEGA; }

        [[nodiscard]] auto kHz() const -> T { return Hz() / KILO; }

        [[nodiscard]] auto Hz() const -> T { return this->value(); }

        auto operator+(const Frequency &other) const -> Frequency {
            return Frequency(Hz() + other.Hz());
        }

        auto operator-(const Frequency &other) const -> Frequency {
            return Frequency(Hz() - other.Hz());
        }

        auto operator*(T scalar) const -> Frequency {
            return Frequency(Hz() * scalar);
        }

        auto operator/(T scalar) const -> Frequency {
            return Frequency(Hz() / scalar);
        }

        friend auto operator*(T lhs, const Frequency<T>& rhs) -> Frequency {
            return Frequency<T>(rhs.Hz() * lhs);
        }
    };

    template<typename T>
    struct UnitMapper<FrequencyUnit<T>> {
        using type = Frequency<T>;
    };
}