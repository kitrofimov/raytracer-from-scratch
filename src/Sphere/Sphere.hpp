#pragma once
#include <limits>
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"
#include "constants.hpp"

class Sphere
{
public:
    Sphere(vec3d position,
           double radius,
           color_t color,
           double shininess = qNaN);
    inline vec3d get_position() { return position; }
    inline double get_radius() { return radius; }
    inline color_t get_color() { return color; }
    inline double get_shininess() { return shininess; }
private:
    vec3d position;
    double radius;
    color_t color;
    double shininess;
};
