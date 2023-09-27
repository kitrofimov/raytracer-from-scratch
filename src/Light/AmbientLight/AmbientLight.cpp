#include "AmbientLight.hpp"
#include "utils/vec/vec3.hpp"

AmbientLight::AmbientLight(double intensity, color_t color)
{
    this->intensity = intensity;
    this->color = color;
}

double AmbientLight::calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                                         std::unique_ptr<Sphere>& p_object)
{
    return this->intensity;
}

vec3d AmbientLight::get_point_to_light_source_vector(vec3d& point)
{
    return vec3d(0, 0, 0);
}
