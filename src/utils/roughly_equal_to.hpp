#pragma once
#include <cmath>
#include "constants.hpp"

// Checks if difference between two values lies within [-tol; tol]
template <typename T>
bool roughly_equal_to(T v1, T v2)
{
    return std::abs(v1 - v2) < tolerance;
}
