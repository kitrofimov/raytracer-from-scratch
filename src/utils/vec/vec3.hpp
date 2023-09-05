#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

template <typename T>
struct vec3
{
public:
    T x = 0;
    T y = 0;
    T z = 0;

    vec3();
    vec3(T x, T y, T z);
    vec3(std::vector<T> vector);

    constexpr T operator[](int i) const;
    constexpr T& operator[](int i);

    constexpr vec3<T> cross_product(vec3<T> rhs) const;
    constexpr vec3<T> normalize() const;
    constexpr double magnitude() const;

    constexpr std::string to_string() const;
};

using vec3i = vec3<int>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;

// Construct a `vec3`, initializing values to 0
template <typename T>
vec3<T>::vec3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

// Construct a `vec3` from three values
template <typename T>
vec3<T>::vec3(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Construct a `vec3` from `std::vector`. Assumes that `std::vector` is of size 3
template <typename T>
vec3<T>::vec3(std::vector<T> vector)
{
    this->x = vector[0];
    this->y = vector[1];
    this->z = vector[2];
}

template <typename T>
constexpr T vec3<T>::operator[](int i) const
{
    switch (i)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    case 2:
        return this->z;
    default:
        throw std::out_of_range("vec3 invalid index " + i);
    }
}

template <typename T>
constexpr T& vec3<T>::operator[](int i)
{
    switch (i)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    case 2:
        return this->z;
    default:
        throw std::out_of_range("vec3 invalid index " + i);
    }
}

template <typename T>
constexpr vec3<T> vec3<T>::cross_product(vec3<T> rhs) const
{
    return vec3<T>(
        this->y * rhs.z - this->z * rhs.y,
        this->z * rhs.x - this->x * rhs.z,
        this->x * rhs.y - this->y * rhs.x
    );
}

template <typename T>
constexpr vec3<T> vec3<T>::normalize() const
{
    double magnitude = this->magnitude();
    return {
        this->x / magnitude,
        this->y / magnitude,
        this->z / magnitude
    };
}

template <typename T>
constexpr double vec3<T>::magnitude() const
{
    return std::sqrt(
        std::pow((double) this->x, 2) + \
        std::pow((double) this->y, 2) + \
        std::pow((double) this->z, 2)
    );
}

template <typename T>
constexpr std::string vec3<T>::to_string() const
{
    std::ostringstream oss;
    oss << "vec3(" << this->x << ", " << this->y << ", " << this->z << ")";
    return oss.str();
}

// Operator overloading

// Addition
template <typename T>
constexpr vec3<T> operator+(vec3<T> lhs, vec3<T> rhs)
{
    return vec3<T>(
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z
    );
}

// Subtraction
template <typename T>
constexpr vec3<T> operator-(vec3<T> lhs, vec3<T> rhs)
{
    return lhs + (-rhs);
}

// Scalar multiplication
template <typename T>
constexpr vec3<T> operator*(vec3<T> lhs, double rhs)
{
    return vec3<T>(
        lhs.x * rhs,
        lhs.y * rhs,
        lhs.z * rhs
    );
}

template <typename T>
constexpr vec3<T> operator*(double lhs, vec3<T> rhs)
{
    return rhs * lhs;
}

// Scalar divide
template <typename T>
constexpr vec3<T> operator/(vec3<T> lhs, double rhs)
{
    return vec3<T>(
        lhs.x / rhs,
        lhs.y / rhs,
        lhs.z / rhs
    );
}

// Negate
template <typename T>
constexpr vec3<T> operator-(vec3<T> lhs)
{
    return vec3<T>(
        -lhs.x,
        -lhs.y,
        -lhs.z
    );
}

// Dot product
template <typename T>
constexpr T operator*(vec3<T> lhs, vec3<T> rhs)
{
    return lhs.x * rhs.x + \
           lhs.y * rhs.y + \
           lhs.z * rhs.z;
}

// Stream insertion operator
template <typename T>
constexpr std::ostream& operator<<(std::ostream& stream, const vec3<T>& vec)
{
    stream << vec.to_string();
    return stream;
}
