#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>
#include "vec3.hpp"

template <typename T>
struct vec2
{
public:
    T x = 0;
    T y = 0;

    vec2();
    vec2(T x, T y);
    vec2(std::vector<T> vector);

    vec2<T> operator+(vec2<T> other) const;
    vec2<T> operator-(vec2<T> other) const;
    vec2<T> operator*(double scalar) const;
    vec2<T> operator/(double scalar) const;
    T operator[](int index) const;
    T& operator[](int index);
    vec2<T> operator-() const;

    vec3<T> cross_product(vec2<T> b) const;
    T dot_product(vec2<T> b) const;
    vec2<T> normalize() const;
    double magnitude() const;

    vec2<float> rotate(float rad, vec2<float> center) const;
    std::string to_string() const;
};

using vec2i = vec2<int>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;

template <typename T>
vec2<T>::vec2()
{
    this->x = 0;
    this->y = 0;
}

template <typename T>
vec2<T>::vec2(T x, T y)
{
    this->x = x;
    this->y = y;
}

template <typename T>
vec2<T>::vec2(std::vector<T> vector)
{
    this->x = vector[0];
    this->y = vector[1];
}

template <typename T>
vec2<T> vec2<T>::operator+(vec2<T> other) const
{
    return {
        this->x + other.x,
        this->y + other.y
    };
}

template <typename T>
vec2<T> vec2<T>::operator-(vec2<T> other) const
{
    return {
        this->x - other.x,
        this->y - other.y
    };
}

template <typename T>
vec2<T> vec2<T>::operator*(double scalar) const
{
    return {
        (T) (this->x * scalar),
        (T) (this->y * scalar)
    };
}

template <typename T>
vec2<T> vec2<T>::operator/(double scalar) const
{
    return {
        (T) (this->x / scalar),
        (T) (this->y / scalar)
    };
}

template <typename T>
T vec2<T>::operator[](int index) const
{
    if (index == 0) return this->x;
    else if (index == 1) return this->y;
    throw std::invalid_argument("vec2 invalid index " + index);
}

template <typename T>
T& vec2<T>::operator[](int index)
{
    if (index == 0) return this->x;
    else if (index == 1) return this->y;
    throw std::invalid_argument("vec2 invalid index " + index);
}

template <typename T>
vec2<T> vec2<T>::operator-() const
{
    return {
        -this->x,
        -this->y
    };
}

template <typename T>
vec3<T> vec2<T>::cross_product(vec2<T> b) const
{
    return vec3<T> {
        (T) 0,
        (T) 0,
        this->x * b.y - this->y * b.x
    };
}

template <typename T>
T vec2<T>::dot_product(vec2<T> b) const
{
    return (this->x * b.x + this->y * b.y);
}

template <typename T>
vec2<T> vec2<T>::normalize() const
{
    // casting to double to avoid ambiguity error if T = int
    double magnitude = this->magnitude();
    return {
        this->x / magnitude,
        this->y / magnitude
    };
}

template <typename T>
double vec2<T>::magnitude() const
{
    return std::sqrt(std::pow((double) this->x, 2) + std::pow((double) this->y, 2));
}

template <typename T>
vec2f vec2<T>::rotate(float rad, vec2f center) const
{
    // the idea is to place `center` at the origin of coordinate system,
    // then rotate the vector and place it to the same exact position as it was before
    vec2f temp = {this->x - center.x, this->y - center.y};
    vec2f result = {
        (temp.x * std::cos(rad)) - (temp.y * std::sin(rad)),
        (temp.x * std::sin(rad)) + (temp.y * std::cos(rad))
    };
    result.x += center.x;
    result.y += center.y;
    return result;
}

template <typename T>
std::string vec2<T>::to_string() const
{
    std::ostringstream oss;
    oss << "vec2(" << this->x << ", " << this->y << ")";
    return oss.str();
}