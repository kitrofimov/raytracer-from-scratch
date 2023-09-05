#pragma once
#include <vector>

template <typename T>
struct vec4;

struct color_t
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;

    color_t();
    color_t(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    color_t(std::vector<unsigned char> vector);
    template <typename T>
    color_t(vec4<T> vec);

    color_t operator+(color_t other) const;
    color_t operator-(color_t other) const;
    color_t operator*(double scalar) const;
    color_t operator/(double scalar) const;
    color_t& operator+=(color_t other);

    template <typename T>
    operator vec4<T>() const;

    unsigned char operator[](int i) const;
    unsigned char& operator[](int i);

    static color_t mix(std::vector<color_t> list);
};
