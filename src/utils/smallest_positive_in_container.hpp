#pragma once
#include <limits>

// Assumes T to be a container of numbers which supports range-based `for` loop.
// Returns quiet NaN if there are no positive numbers at all.
template <typename T>
inline typename T::value_type smallest_positive_in_container(T& container)
{
    using value_t = typename T::value_type;
    value_t result = std::numeric_limits<value_t>::max();
    for (auto& value : container)
    {
        if ((value < result) && (value > 0))
            result = value;
    }
    if (result == std::numeric_limits<value_t>::max())  // there are no positive numbers in container
        result = std::numeric_limits<value_t>::quiet_NaN();
    return result;
}
