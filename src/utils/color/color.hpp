#pragma once
#include <vector>

template <typename T>
struct vec4;
using vec4d = vec4<double>;

struct color_t
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;

    color_t();
    color_t(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    color_t(std::vector<unsigned char> vector);

    color_t operator+(color_t other) const;
    color_t operator-(color_t other) const;
    color_t operator*(double scalar) const;
    color_t operator/(double scalar) const;
    color_t& operator+=(color_t other);

    unsigned char operator[](int i) const;
    unsigned char& operator[](int i);

    operator vec4d() const;

    static color_t mix(std::vector<color_t> list);
};
