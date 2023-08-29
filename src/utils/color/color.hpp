#pragma once

struct color_t
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;

    color_t operator*(double scalar);
    color_t operator/(double scalar);
    color_t operator+(color_t other);
    color_t operator+=(color_t other);
    color_t operator-(color_t other);
};
