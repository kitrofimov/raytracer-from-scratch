#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

template <typename T>
struct vec2
{
public:
    T x = 0;
    T y = 0;

    vec2();
    vec2(T x, T y);
    vec2(std::vector<T> vector);

    constexpr T operator[](int i) const;
    constexpr T& operator[](int i);

    constexpr vec2<T> normalize() const;
    constexpr double magnitude() const;
    constexpr vec2<T> rotate(double rad, vec2<T> center) const;

    constexpr std::string to_string() const;
};

using vec2i = vec2<int>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;

// Construct a `vec2`, initializing values to 0
template <typename T>
vec2<T>::vec2()
{
    this->x = 0;
    this->y = 0;
}

// Construct a `vec2` from two values
template <typename T>
vec2<T>::vec2(T x, T y)
{
    this->x = x;
    this->y = y;
}

// Construct a `vec2` from `std::vector`. Assumes that `std::vector` is of size 2
template <typename T>
vec2<T>::vec2(std::vector<T> vector)
{
    this->x = vector[0];
    this->y = vector[1];
}

template <typename T>
constexpr T vec2<T>::operator[](int i) const
{
    switch (i)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    default:
        throw std::out_of_range("vec2 invalid index " + i);
    }
}

template <typename T>
constexpr T& vec2<T>::operator[](int i)
{
    switch (i)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    default:
        throw std::out_of_range("vec2 invalid index " + i);
    }
}

template <typename T>
constexpr vec2<T> vec2<T>::normalize() const
{
    double magnitude = this->magnitude();
    return vec2<T>(
        this->x / magnitude,
        this->y / magnitude
    );
}

template <typename T>
constexpr double vec2<T>::magnitude() const
{
    return std::sqrt(std::pow((double) this->x, 2) + std::pow((double) this->y, 2));
}

template <typename T>
constexpr vec2<T> vec2<T>::rotate(double rad, vec2<T> center) const
{
    vec2<T> temp = {this->x - center.x, this->y - center.y};  // place center at the origin
    vec2<T> result = {  // rotate
        (temp.x * std::cos(rad)) - (temp.y * std::sin(rad)),
        (temp.x * std::sin(rad)) + (temp.y * std::cos(rad))
    };
    result.x += center.x;  // place them where they were before
    result.y += center.y;
    return result;
}

template <typename T>
constexpr std::string vec2<T>::to_string() const
{
    std::ostringstream oss;
    oss << "vec2(" << this->x << ", " << this->y << ")";
    return oss.str();
}

// Operator overloading

// Addition
template <typename T>
constexpr vec2<T> operator+(vec2<T> lhs, vec2<T> rhs)
{
    return vec2<T>(
        lhs.x + rhs.x,
        lhs.y + rhs.y
    );
}

// Subtraction
template <typename T>
constexpr vec2<T> operator-(vec2<T> lhs, vec2<T> rhs)
{
    return lhs + (-rhs);
}

// Scalar multiplication
template <typename T>
constexpr vec2<T> operator*(vec2<T> lhs, double rhs)
{
    return vec2<T>(
        lhs.x * rhs,
        lhs.y * rhs
    );
}

template <typename T>
constexpr vec2<T> operator*(double lhs, vec2<T> rhs)
{
    return rhs * lhs;
}

// Scalar divide
template <typename T>
constexpr vec2<T> operator/(vec2<T> lhs, double rhs)
{
    return vec2<T>(
        lhs.x / rhs,
        lhs.y / rhs
    );
}

// Negate
template <typename T>
constexpr vec2<T> operator-(vec2<T> lhs)
{
    return vec2<T>(
        -lhs.x
        -lhs.y
    );
}

// Dot product
template <typename T>
constexpr T operator*(vec2<T> lhs, vec2<T> rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// Stream insertion operator
template <typename T>
constexpr std::ostream& operator<<(std::ostream& stream, const vec2<T>& vec)
{
    stream << vec.to_string();
    return stream;
}
