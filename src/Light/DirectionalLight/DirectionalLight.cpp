#include "DirectionalLight.hpp"
#include "utils/vec/vec3.hpp"

DirectionalLight::DirectionalLight(double intensity, vec3d direction)
{
    this->intensity = intensity;
    this->direction = direction.normalize();
}

double DirectionalLight::calculate_intensity(vec3d point, vec3d normal)
{
    // light direction vector (point -> light source)
    vec3d L = -this->direction;
    double calculated = normal.dot_product(L) / (normal.magnitude() * L.magnitude());
    calculated = (calculated < 0) ? 0 : calculated;  // clamp at 0 if < 0
    return this->intensity * calculated;
}
