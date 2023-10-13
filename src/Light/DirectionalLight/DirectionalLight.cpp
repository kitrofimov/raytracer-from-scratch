#include "Sphere/Sphere.hpp"
#include "DirectionalLight.hpp"
#include "utils/vec/vec3.hpp"

DirectionalLight::DirectionalLight(double intensity, Color color, vec3d direction)
{
    this->intensity = intensity;
    this->color = color;
    this->direction = direction.normalize();
}

vec3d DirectionalLight::get_point_to_light_source_vector(vec3d& point)
{
    return -this->direction;
}

LightSourceType DirectionalLight::get_type()
{
    return LightSourceType::DirectionalLight;
}
