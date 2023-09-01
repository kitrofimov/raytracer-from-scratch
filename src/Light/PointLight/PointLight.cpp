#include <cmath>
#include "PointLight.hpp"
#include "utils/vec/vec3.hpp"

PointLight::PointLight(double intensity, vec3d position)
{
    this->intensity = intensity;
    this->position = position;
}

double PointLight::calculate_intensity(vec3d point, vec3d normal, vec3d camera, std::unique_ptr<Sphere>& p_object)
{
    // light direction vector (point -> light source)
    vec3d L = this->position - point;
    return this->_calculate_intensity(point, L, normal, camera, p_object);
}
