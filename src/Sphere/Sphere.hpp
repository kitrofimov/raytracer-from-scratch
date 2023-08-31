#pragma once
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

class Sphere
{
public:
    Sphere(vec3d center, double radius, color_t color);
    inline vec3d get_position() { return position; }
    inline double get_radius() { return radius; }
    inline color_t get_color() { return color; }
private:
    vec3d position;
    double radius;
    color_t color;
};
