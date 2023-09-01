#pragma once

template <typename T>
inline void clamp_at_zero(T& a)
{
    a = (a < 0) ? 0 : a;
}
