#pragma once

// if m == 0 => return a
// if m == 1 => return b
// if m in (0, 1) => return interpolated value
template <typename T>
inline T lerp(T& a, T& b, double& m)
{
    return a * (1 - m) + b * m;
}
