/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <cstdint>
#include "utl/base/time.hpp"

namespace utl {

    // Precise, integer-native time built on top of Time<int64_t>. The tick is a
    // nanosecond. These types deliberately expose only additive (affine) and
    // scaling operations -- no inv()/sqrt/float division -- so the existing
    // floating-point unit machinery is untouched. Use to_time() to cross into
    // the dimensional Time<double> (seconds) world.

    class TimeDuration {
        Time<int64_t> ticks_; // nanoseconds

    public:
        constexpr explicit TimeDuration(int64_t nanoseconds) : ticks_{nanoseconds} {}

        [[nodiscard]] constexpr auto ns() const -> int64_t { return ticks_.value(); }

        [[nodiscard]] constexpr auto us() const -> int64_t { return ticks_.value() / 1000; }

        [[nodiscard]] constexpr auto ms() const -> int64_t { return ticks_.value() / 1000000; }

        [[nodiscard]] constexpr auto s() const -> int64_t { return ticks_.value() / 1000000000; }

        [[nodiscard]] constexpr auto to_time() const -> Time<double> { return Time<double>(static_cast<double>(ticks_.value()) * 1e-9); }

        constexpr auto operator+(const TimeDuration &other) const -> TimeDuration { return TimeDuration(ns() + other.ns()); }

        constexpr auto operator-(const TimeDuration &other) const -> TimeDuration { return TimeDuration(ns() - other.ns()); }

        constexpr auto operator-() const -> TimeDuration { return TimeDuration(-ns()); }

        constexpr auto operator*(int64_t scalar) const -> TimeDuration { return TimeDuration(ns() * scalar); }

        constexpr auto operator/(int64_t scalar) const -> TimeDuration { return TimeDuration(ns() / scalar); }

        friend constexpr auto operator*(int64_t scalar, const TimeDuration &d) -> TimeDuration { return TimeDuration(d.ns() * scalar); }

        constexpr auto operator==(const TimeDuration &other) const -> bool { return ns() == other.ns(); }
        constexpr auto operator!=(const TimeDuration &other) const -> bool { return ns() != other.ns(); }
        constexpr auto operator<(const TimeDuration &other) const -> bool { return ns() < other.ns(); }
        constexpr auto operator<=(const TimeDuration &other) const -> bool { return ns() <= other.ns(); }
        constexpr auto operator>(const TimeDuration &other) const -> bool { return ns() > other.ns(); }
        constexpr auto operator>=(const TimeDuration &other) const -> bool { return ns() >= other.ns(); }
    };

    class TimeStamp {
        Time<int64_t> since_epoch_; // nanoseconds since an unspecified epoch

    public:
        constexpr explicit TimeStamp(int64_t ns_since_epoch) : since_epoch_{ns_since_epoch} {}

        [[nodiscard]] constexpr auto ns() const -> int64_t { return since_epoch_.value(); }

        [[nodiscard]] constexpr auto time_since_epoch() const -> TimeDuration { return TimeDuration(since_epoch_.value()); }

        constexpr auto operator-(const TimeStamp &other) const -> TimeDuration { return TimeDuration(ns() - other.ns()); }

        constexpr auto operator+(const TimeDuration &d) const -> TimeStamp { return TimeStamp(ns() + d.ns()); }

        constexpr auto operator-(const TimeDuration &d) const -> TimeStamp { return TimeStamp(ns() - d.ns()); }

        // Adding two absolute timestamps is physically meaningless.
        auto operator+(const TimeStamp &other) const -> TimeStamp = delete;

        constexpr auto operator==(const TimeStamp &other) const -> bool { return ns() == other.ns(); }
        constexpr auto operator!=(const TimeStamp &other) const -> bool { return ns() != other.ns(); }
        constexpr auto operator<(const TimeStamp &other) const -> bool { return ns() < other.ns(); }
        constexpr auto operator<=(const TimeStamp &other) const -> bool { return ns() <= other.ns(); }
        constexpr auto operator>(const TimeStamp &other) const -> bool { return ns() > other.ns(); }
        constexpr auto operator>=(const TimeStamp &other) const -> bool { return ns() >= other.ns(); }
    };

    constexpr auto nanoseconds(int64_t n) -> TimeDuration { return TimeDuration(n); }

    constexpr auto microseconds(int64_t n) -> TimeDuration { return TimeDuration(n * 1000); }

    constexpr auto milliseconds(int64_t n) -> TimeDuration { return TimeDuration(n * 1000000); }

    constexpr auto seconds(int64_t n) -> TimeDuration { return TimeDuration(n * 1000000000); }

} // namespace utl
