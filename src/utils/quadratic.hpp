#pragma once

#include <array>
#include <limits>
#include <cmath>
#include "constants.hpp"
#include "quadratic.hpp"

// Solve ax^2 + bx + c = 0
template <typename T>
std::array<T, 2> solve_quadratic(T a, T b, T c)
{
    T D = b*b - 4.0*a*c;
    if (D < 0)
        return {qNaN, qNaN};
    return {
        (-b + std::sqrt(D)) / (2*a),
        (-b - std::sqrt(D)) / (2*a)
    };
}

// Assumes T to be a container of numbers which supports range-based `for` loop.
// Returns quiet NaN if there are no positive numbers at all.
template <typename T>
typename T::value_type smallest_positive_in_container(T& container)
{
    using value_t = typename T::value_type;
    value_t result = std::numeric_limits<value_t>::max();
    for (auto& value : container)
    {
        if ((value < result) && (value > tolerance))
            result = value;
    }
    if (result == std::numeric_limits<value_t>::max())  // there are no positive numbers in container
        result = std::numeric_limits<value_t>::quiet_NaN();
    return result;
}

template <typename T>
inline T solve_quadratic_for_smallest_positive(T a, T b, T c)
{
    auto solutions = solve_quadratic(a, b, c);
    return smallest_positive_in_container(solutions);
}
