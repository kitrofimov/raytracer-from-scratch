#pragma once
#include "Object.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

class Sphere : public Object
{
public:
    Sphere(vec3d center, double radius, color_t color);
private:
    double radius;
    color_t color;
};
