#pragma once
#include <array>

// =================
// Class declaration
// =================

template <typename T, std::size_t N>
class vec
{
public:
    vec();
    vec(std::initializer_list<T> values);

    auto begin() const;
    auto end() const;

    T operator[](std::size_t i) const;
    T& operator[](std::size_t i);

    T x() const { return this->data[0]; }
    T& x() { return this->data[0]; }
    T y() const { return this->data[1]; }
    T& y() { return this->data[1]; }
    T z() const { return this->data[2]; }
    T& z() { return this->data[2]; }
    T w() const { return this->data[3]; }
    T& w() { return this->data[3]; }
private:
    std::array<T, N> data;
};

// ============
// Type aliases
// ============

template <typename T>
using vec2 = vec<T, 2>;
using vec2i = vec<int, 2>;
using vec2f = vec<float, 2>;
using vec2d = vec<double, 2>;

template <typename T>
using vec3 = vec<T, 3>;
using vec3i = vec<int, 3>;
using vec3f = vec<float, 3>;
using vec3d = vec<double, 3>;

template <typename T>
using vec4 = vec<T, 4>;
using vec4i = vec<int, 4>;
using vec4f = vec<float, 4>;
using vec4d = vec<double, 4>;

// ================
// Class definition
// ================

template <typename T, std::size_t N>
vec<T, N>::vec()
{
    for (auto& value : this->data)
        value = 0;
}

template <typename T, std::size_t N>
vec<T, N>::vec(std::initializer_list<T> values)
{
    std::size_t i = 0;
    // there is no operator[] for initializer list, so using this
    for (auto& value : values)
    {
        this->data[i] = value;
        i++;
    }
}

template <typename T, std::size_t N>
auto vec<T, N>::begin() const
{
    return this->data.begin();
}

template <typename T, std::size_t N>
auto vec<T, N>::end() const
{
    return this->data.end();
}

template <typename T, std::size_t N>
T vec<T, N>::operator[](std::size_t i) const
{
    return this->data[i];
}

template <typename T, std::size_t N>
T& vec<T, N>::operator[](std::size_t i)
{
    return this->data[i];
}

// ===============================
// Non-member operator overloading
// ===============================

// Add two vectors
template <typename T, std::size_t N>
auto operator+(vec<T, N> lhs, vec<T, N> rhs)
{
    vec<T, N> result;
    for (std::size_t i = 0; i < N; i++)
        result[i] = lhs[i] + rhs[i];
    return result;
}

// Subtract two vectors
template <typename T, std::size_t N>
auto operator-(vec<T, N> lhs, vec<T, N> rhs)
{
    return lhs + (-rhs);
}

// Negate a vector
template <typename T, std::size_t N>
auto operator-(vec<T, N> vec)
{
    return -1 * vec;
}

// Dot product of two vectors
template <typename T, std::size_t N>
auto operator*(vec<T, N> lhs, vec<T, N> rhs)
{
    T result = 0;
    for (std::size_t i = 0; i < N; i++)
        result += lhs[i] * rhs[i];
    return result;
}

// Scalar multiplication
template <typename T, std::size_t N>
auto operator*(vec<T, N> lhs, T rhs)
{
    vec<T, N> result;
    for (std::size_t i = 0; i < N; i++)
        result[i] = lhs[i] * rhs;
    return result;
}

// Scalar multiplication
template <typename T, std::size_t N>
auto operator*(T lhs, vec<T, N> rhs)
{
    return rhs * lhs;
}

// Cross product of two (3-dimensional!) vectors
template <typename T, std::size_t N>
auto cross_product(vec<T, N> lhs, vec<T, N> rhs)
{
    static_assert(N != 7, "Sorry, cross product for 7 dimensional vectors is not implemented!");
    static_assert(N == 3, "Cross product is defined only in 3 and 7 dimensions (sorry, cross product for 7 dimensional vectos is not implemented)");

    return vec<T, 3> {
        lhs[1] * rhs[2] - rhs[1] * lhs[2],
        lhs[2] * rhs[0] - rhs[2] * lhs[0],
        lhs[0] * rhs[1] - rhs[0] * lhs[1]
    };
}

// Vector equality
template <typename T, std::size_t N>
auto operator==(vec<T, N> lhs, vec<T, N> rhs)
{
    for (std::size_t i = 0; i < N; i++)
        if (lhs[i] != rhs[i]) return false;
    return true;
}

// Vector inequality
template <typename T, std::size_t N>
auto operator!=(vec<T, N> lhs, vec<T, N> rhs)
{
    return !(lhs == rhs);
}

// Stream insertion operator
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& stream, const vec<T, N>& rhs)
{
    stream << "vec<" << typeid(T).name() << ", " << N << "> {";
    for (std::size_t i = 0; i < N; i++)
    {
        if (i != 0)
            stream << ", ";
        stream << rhs[i];
    }
    stream << "}";
    return stream;
}
