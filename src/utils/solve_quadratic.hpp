#pragma once
#include <array>
#include "constants.hpp"

// Solve ax^2 + bx + c = 0
template <typename T>
inline std::array<T, 2> solve_quadratic(T a, T b, T c)
{
    T D = b*b - 4.0*a*c;
    if (D < 0)
        return {qNaN, qNaN};
    return {
        (-b + std::sqrt(D)) / 2*a,
        (-b - std::sqrt(D)) / 2*a
    };
}
