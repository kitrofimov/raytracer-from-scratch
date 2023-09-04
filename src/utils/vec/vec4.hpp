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

    vec4<T> operator+(vec4<T> other) const;
    vec4<T> operator+(color_t other) const;
    vec4<T> operator-(vec4<T> other) const;
    vec4<T> operator*(double scalar) const;
    vec4<T> operator*(color_t other) const;
    vec4<T> operator/(double scalar) const;
    T operator[](int index) const;
    T& operator[](int index);
    vec4<T> operator-() const;

    operator color_t() const { return (color_t) {(unsigned char) this->x, (unsigned char) this->y, (unsigned char) this->z, (unsigned char) this->w}; };

    T dot_product(vec4<T> b) const;
    vec4<T> normalize() const;
    double magnitude() const;

    std::string to_string() const;
};

using vec4i = vec4<int>;
using vec4f = vec4<float>;
using vec4d = vec4<double>;

template <typename T>
vec4<T>::vec4()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

template <typename T>
vec4<T>::vec4(T x, T y, T z, T w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

template <typename T>
vec4<T>::vec4(std::vector<T> vector)
{
    this->x = vector[0];
    this->y = vector[1];
    this->z = vector[2];
    this->w = vector[3];
}

template <typename T>
vec4<T> vec4<T>::operator+(vec4<T> other) const
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z,
        this->w + other.w
    };
}

template <typename T>
vec4<T> vec4<T>::operator+(color_t other) const
{
    return {
        this->x + other.r,
        this->y + other.g,
        this->z + other.b,
        this->w + other.a
    };
}

template <typename T>
vec4<T> vec4<T>::operator-(vec4<T> other) const
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z,
        this->w - other.w
    };
}

template <typename T>
vec4<T> vec4<T>::operator*(double scalar) const
{
    return {
        (T) (this->x * scalar),
        (T) (this->y * scalar),
        (T) (this->z * scalar),
        (T) (this->w * scalar)
    };
}

template <typename T>
vec4<T> vec4<T>::operator*(color_t other) const
{
    return {
        this->x * other.r,
        this->y * other.g,
        this->z * other.b,
        this->w * other.a
    };
}

template <typename T>
vec4<T> vec4<T>::operator/(double scalar) const
{
    return {
        (T) (this->x / scalar),
        (T) (this->y / scalar),
        (T) (this->z / scalar),
        (T) (this->w / scalar)
    };
}

template <typename T>
T vec4<T>::operator[](int index) const
{
    if (index == 0) return this->x;
    else if (index == 1) return this->y;
    else if (index == 2) return this->z;
    else if (index == 3) return this->w;
    throw std::invalid_argument("vec4 invalid index " + index);
}

template <typename T>
T& vec4<T>::operator[](int index)
{
    if (index == 0) return this->x;
    else if (index == 1) return this->y;
    else if (index == 2) return this->z;
    else if (index == 3) return this->w;
    throw std::invalid_argument("vec4 invalid index " + index);
}

template <typename T>
vec4<T> vec4<T>::operator-() const
{
    return {
        -this->x,
        -this->y,
        -this->z,
        -this->w
    };
}

template <typename T>
T vec4<T>::dot_product(vec4<T> b) const
{
    return (this->x * b.x + this->y * b.y + this->z * b.z + this->w * b.w);
}

template <typename T>
vec4<T> vec4<T>::normalize() const
{
    // casting to double to avoid ambiguity error if T = int
    double magnitude = this->magnitude();
    return {
        this->x / magnitude,
        this->y / magnitude,
        this->z / magnitude,
        this->w / magnitude
    };
}

template <typename T>
double vec4<T>::magnitude() const
{
    return std::sqrt(std::pow((double) this->x, 2) + std::pow((double) this->y, 2) + std::pow((double) this->z, 2) + std::pow((double) this->w, 2));
}

template <typename T>
std::string vec4<T>::to_string() const
{
    std::ostringstream oss;
    oss << "vec4(" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")";
    return oss.str();
}
