#include "Sphere/Sphere.hpp"
#include "DirectionalLight.hpp"
#include "utils/vec/vec3.hpp"

DirectionalLight::DirectionalLight(double intensity, color_t color, vec3d direction)
{
    this->intensity = intensity;
    this->color = color;
    this->direction = direction.normalize();
}

double DirectionalLight::calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                                             std::unique_ptr<Sphere>& p_object)
{
    // light direction vector (point -> light source)
    vec3d L = -this->direction;
    return this->_calculate_intensity(point, L, normal, camera_pos, p_object);
}
