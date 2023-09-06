#pragma once
#include <stdexcept>
#include <sstream>
#include "vec3.hpp"
#include "utils/color/color.hpp"

template <typename T>
struct vec4
{
public:
    T x = 0;
    T y = 0;
    T z = 0;
    T w = 0;

    vec4();
    vec4(T x, T y, T z, T w);
    vec4(std::vector<T> vector);

    constexpr T operator[](int i) const;
    constexpr T& operator[](int i);

    constexpr vec4<T> normalize() const;
    constexpr double magnitude() const;

    constexpr std::string to_string() const;
};

using vec4i = vec4<int>;
using vec4f = vec4<float>;
using vec4d = vec4<double>;

// Construct a `vec4`, initializing values to 0
template <typename T>
vec4<T>::vec4()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

// Construct a `vec4` from four values
template <typename T>
vec4<T>::vec4(T x, T y, T z, T w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

// Construct a `vec4` from `std::vector`. Assumes that `std::vector` is of size 4
template <typename T>
vec4<T>::vec4(std::vector<T> vector)
{
    this->x = vector[0];
    this->y = vector[1];
    this->z = vector[2];
    this->w = vector[3];
}

template <typename T>
constexpr T vec4<T>::operator[](int i) const
{
    switch (i)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    case 2:
        return this->z;
    case 3:
        return this->w;
    default:
        throw std::out_of_range("vec4 invalid index " + i);
    }
}

template <typename T>
constexpr T& vec4<T>::operator[](int i)
{
    switch (i)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    case 2:
        return this->z;
    case 3:
        return this->w;
    default:
        throw std::out_of_range("vec4 invalid index " + i);
    }
}

template <typename T>
constexpr vec4<T> vec4<T>::normalize() const
{
    double magnitude = this->magnitude();
    return {
        this->x / magnitude,
        this->y / magnitude,
        this->z / magnitude,
        this->w / magnitude
    };
}

template <typename T>
constexpr double vec4<T>::magnitude() const
{
    return std::sqrt(
        std::pow((double) this->x, 2) + \
        std::pow((double) this->y, 2) + \
        std::pow((double) this->z, 2) + \
        std::pow((double) this->w, 2)
    );
}

template <typename T>
constexpr std::string vec4<T>::to_string() const
{
    std::ostringstream oss;
    oss << "vec4(" << this->x << ", "
                   << this->y << ", "
                   << this->z << ", "
                   << this->w << ")";
    return oss.str();
}

// Operator overloading

// Addition
template <typename T>
constexpr vec4<T> operator+(vec4<T> lhs, vec4<T> rhs)
{
    return vec4<T>(
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w
    );
}

// Subtraction
template <typename T>
constexpr vec4<T> operator-(vec4<T> lhs, vec4<T> rhs)
{
    return lhs + (-rhs);
}

// Scalar multiplication
template <typename T>
constexpr vec4<T> operator*(vec4<T> lhs, double rhs)
{
    return vec4<T>(
        lhs.x * rhs,
        lhs.y * rhs,
        lhs.z * rhs,
        lhs.w * rhs
    );
}

template <typename T>
constexpr vec4<T> operator*(double lhs, vec4<T> rhs)
{
    return rhs * lhs;
}

// Scalar divide
template <typename T>
constexpr vec4<T> operator/(vec4<T> lhs, double rhs)
{
    return vec4<T>(
        lhs.x / rhs,
        lhs.y / rhs,
        lhs.z / rhs,
        lhs.w / rhs
    );
}

// Negate
template <typename T>
constexpr vec4<T> operator-(vec4<T> lhs)
{
    return vec4<T>(
        -lhs.x,
        -lhs.y,
        -lhs.z,
        -lhs.w
    );
}

// Dot product
template <typename T>
constexpr T operator*(vec4<T> lhs, vec4<T> rhs)
{
    return lhs.x * rhs.x + \
           lhs.y * rhs.y + \
           lhs.z * rhs.z + \
           lhs.w * rhs.w;
}

// Comparison
template <typename T>
constexpr T operator==(vec4<T> lhs, vec4<T> rhs)
{
    return lhs.x == rhs.x && \
           lhs.y == rhs.y && \
           lhs.z == rhs.z && \
           lhs.w == rhs.w;
}

template <typename T>
constexpr T operator!=(vec4<T> lhs, vec4<T> rhs)
{
    return !(lhs == rhs);
}

// Stream insertion operator
template <typename T>
constexpr std::ostream& operator<<(std::ostream& stream, const vec4<T>& vec)
{
    stream << vec.to_string();
    return stream;
}
