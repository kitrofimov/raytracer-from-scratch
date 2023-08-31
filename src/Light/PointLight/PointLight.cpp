#include "PointLight.hpp"
#include "utils/vec/vec3.hpp"

PointLight::PointLight(double intensity, vec3d position)
{
    this->intensity = intensity;
    this->position = position;
}

double PointLight::calculate_intensity(vec3d point, vec3d normal)
{
    // light direction vector (point -> light source)
    vec3d L = this->position - point;
    double calculated = normal.dot_product(L) / (normal.magnitude() * L.magnitude());
    calculated = (calculated < 0) ? 0 : calculated;  // clamp at 0 if < 0
    return this->intensity * calculated;
}
