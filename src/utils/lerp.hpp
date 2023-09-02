#pragma once
#include <utility>

// Lerp function. t = 1 => full b; t = 0 => full a
template <typename T>
inline T lerp(T a, T b, double t)
{
    return (1 - t)*a + t*b;
}

// Lerp for multiple values
template <typename T>
inline T multiple_lerp(std::initializer_list<std::pair<T, double>> lists)
{
    T result;
    double sum_of_ts = 0;
    for (auto& list : lists)
    {
        result = result + list.first * list.second;
        sum_of_ts += list.second;
    }
    result = result / sum_of_ts;
    return result;
}

// Lerp for multiple values
template <typename T>
inline T multiple_lerp(std::vector<std::pair<T, double>> lists)
{
    T result;
    double sum_of_ts = 0;
    for (auto& list : lists)
    {
        result = result + list.first * list.second;
        sum_of_ts += list.second;
    }
    result = result / sum_of_ts;
    return result;
}
