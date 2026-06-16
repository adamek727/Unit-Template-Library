# Introduction

Unit Template Library (UTL) is an easy to use, header-only C++17 library for
type-safe SI units.

Every quantity is represented by its seven SI base dimension exponents (time,
length, mass, electric current, thermodynamic temperature, amount of
substance, luminous intensity) plus an eighth *angle* pseudo-dimension
(`rad` = angle¹, `sr` = angle²), all encoded as template parameters. The
compiler tracks dimensions through arithmetic, so adding a `Length` to a `Time`
is a compile-time error, while dividing a `Length` by a `Time` yields a
`Velocity`.

The library is the successor of the
[Robotic Template Library](https://github.com/Robotics-BUT/Robotic-Template-Library).

## Design goals

- **Type safety** — dimension errors are caught at compile time.
- **Zero overhead** — a unit is exactly one float or double at runtime.
- **Header-only** — nothing to build or link; include and go.

## License

MIT License, Copyright (c) 2024 Adam Ligocki.

## Feedback

For technical feedback, bug reports, or feature proposals please use the
[GitHub issue tracker](https://github.com/adamek727/Unit-Template-Library/issues).
