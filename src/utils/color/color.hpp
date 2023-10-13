#pragma once
#include <vector>

template <typename T>
struct vec4;

struct Color
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;

    Color();
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    Color(std::vector<unsigned char> vector);
    template <typename T>
    Color(vec4<T> vec);

    Color operator+(Color other) const;
    Color operator-(Color other) const;
    Color operator*(double scalar) const;
    Color operator/(double scalar) const;
    Color& operator+=(Color other);

    template <typename T>
    operator vec4<T>() const;

    unsigned char operator[](int i) const;
    unsigned char& operator[](int i);

    static Color mix(std::vector<Color> list);
};
