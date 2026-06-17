/*
 * Copyright (C) 2024 Adam Ligocki
 * Distributed under MIT licence
 */

#pragma once

#include <chrono>
#include <cstdint>
#include "utl/time_point.hpp"

// Opt-in interop between the precise-time types (utl/time_point.hpp) and
// std::chrono. Kept out of time_point.hpp so that <chrono> is only pulled in
// when this header is included; nothing here affects the dimensional units.

namespace utl {

    template<typename Rep, typename Period>
    constexpr auto to_duration(const std::chrono::duration<Rep, Period> &d) -> TimeDuration {
        return TimeDuration(std::chrono::duration_cast<std::chrono::nanoseconds>(d).count());
    }

    constexpr auto to_chrono(const TimeDuration &d) -> std::chrono::nanoseconds {
        return std::chrono::nanoseconds(d.ns());
    }

    template<typename Clock, typename Duration>
    constexpr auto to_timestamp(const std::chrono::time_point<Clock, Duration> &tp) -> TimeStamp {
        return TimeStamp(std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count());
    }

    template<typename Clock>
    constexpr auto to_chrono(const TimeStamp &ts) -> std::chrono::time_point<Clock, std::chrono::nanoseconds> {
        return std::chrono::time_point<Clock, std::chrono::nanoseconds>(std::chrono::nanoseconds(ts.ns()));
    }

} // namespace utl
