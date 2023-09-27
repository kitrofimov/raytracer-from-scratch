#include <cmath>
#include "PointLight.hpp"
#include "utils/vec/vec3.hpp"

PointLight::PointLight(double intensity, color_t color, vec3d position)
{
    this->intensity = intensity;
    this->color = color;
    this->position = position;
}

vec3d PointLight::get_point_to_light_source_vector(vec3d& point)
{
    return this->position - point;
}
