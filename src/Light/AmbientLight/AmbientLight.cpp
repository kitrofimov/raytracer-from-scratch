#include "AmbientLight.hpp"
#include "utils/vec/vec3.hpp"

AmbientLight::AmbientLight(double intensity)
{
    this->intensity = intensity;
}

double AmbientLight::calculate_intensity(vec3d point, vec3d normal)
{
    return this->intensity;
}
