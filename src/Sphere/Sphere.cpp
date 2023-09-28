#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"
#include "Sphere.hpp"

Sphere::Sphere(vec3d position, double radius, color_t color, double shininess, double reflectiveness)
{
    this->position = position;
    this->radius = radius;
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;
}
