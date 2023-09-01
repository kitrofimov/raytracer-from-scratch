#include "AmbientLight.hpp"
#include "utils/vec/vec3.hpp"

AmbientLight::AmbientLight(double intensity)
{
    this->intensity = intensity;
}

double AmbientLight::calculate_intensity(vec3d point, vec3d normal, vec3d camera, std::unique_ptr<Sphere>& p_object)
{
    return this->intensity;
}
