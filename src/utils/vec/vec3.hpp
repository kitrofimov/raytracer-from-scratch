#pragma once
#include <stdexcept>
#include <cmath>
#include <sstream>
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

    vec3<T> operator+(vec3<T> other) const;
    vec3<T> operator-(vec3<T> other) const;
    vec3<T> operator*(double scalar) const;
    vec3<T> operator/(double scalar) const;
    T operator[](int index) const;
    T& operator[](int index);
    vec3<T> operator-() const;

    vec3<T> cross_product(vec3<T> b) const;
    T dot_product(vec3<T> b) const;
    vec3<T> normalize() const;
    double magnitude() const;

    std::string to_string() const;
};

using vec3i = vec3<int>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;

template <typename T>
vec3<T>::vec3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template <typename T>
vec3<T>::vec3(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
vec3<T>::vec3(std::vector<T> vector)
{
    this->x = vector[0];
    this->y = vector[1];
    this->z = vector[2];
}

template <typename T>
vec3<T> vec3<T>::operator+(vec3<T> other) const
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z
    };
}

template <typename T>
vec3<T> vec3<T>::operator-(vec3<T> other) const
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z
    };
}

template <typename T>
vec3<T> vec3<T>::operator*(double scalar) const
{
    return {
        (T) (this->x * scalar),
        (T) (this->y * scalar),
        (T) (this->z * scalar)
    };
}

template <typename T>
vec3<T> vec3<T>::operator/(double scalar) const
{
    return {
        (T) (this->x / scalar),
        (T) (this->y / scalar),
        (T) (this->z / scalar)
    };
}

template <typename T>
T vec3<T>::operator[](int index) const
{
    if (index == 0) return this->x;
    else if (index == 1) return this->y;
    else if (index == 2) return this->z;
    throw std::invalid_argument("vec3 invalid index " + index);
}

template <typename T>
T& vec3<T>::operator[](int index)
{
    if (index == 0) return this->x;
    else if (index == 1) return this->y;
    else if (index == 2) return this->z;
    throw std::invalid_argument("vec3 invalid index " + index);
}

template <typename T>
vec3<T> vec3<T>::operator-() const
{
    return {
        -this->x,
        -this->y,
        -this->z
    };
}

template <typename T>
vec3<T> vec3<T>::cross_product(vec3<T> b) const
{
    return vec3<T> {
        this->y * b.z - this->z * b.y,
        this->z * b.x - this->x * b.z,
        this->x * b.y - this->y * b.x
    };
}

template <typename T>
T vec3<T>::dot_product(vec3<T> b) const
{
    return (this->x * b.x + this->y * b.y + this->z * b.z);
}

template <typename T>
vec3<T> vec3<T>::normalize() const
{
    // casting to double to avoid ambiguity error if T = int
    double magnitude = this->magnitude();
    return {
        this->x / magnitude,
        this->y / magnitude,
        this->z / magnitude
    };
}

template <typename T>
double vec3<T>::magnitude() const
{
    return std::sqrt(std::pow((double) this->x, 2) + std::pow((double) this->y, 2) + std::pow((double) this->z, 2));
}

template <typename T>
std::string vec3<T>::to_string() const
{
    std::ostringstream oss;
    oss << "vec3(" << this->x << ", " << this->y << ", " << this->z << ")";
    return oss.str();
}
