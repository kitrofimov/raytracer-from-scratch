#pragma once

// Checks whether or not specified value is in [min, max] range
template <typename T1, typename T2, typename T3>
inline bool in_range(T1 value, T2 min, T3 max)
{
    if (value >= min && value <= max)
        return true;
    return false;
}
