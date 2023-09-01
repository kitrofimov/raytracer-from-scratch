#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"
#include "Sphere.hpp"

Sphere::Sphere(vec3d center, double radius, color_t color, double shininess)
{
    this->position = center;
    this->radius = radius;
    this->color = color;
    this->shininess = shininess;
}
