#include <memory>
#include "LightSource.hpp"
#include "Sphere/Sphere.hpp"
#include "utils/clamp_at_zero.hpp"
#include "utils/reflect_ray.hpp"

// Calculate intensity of light at some point
double LightSource::calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                                        std::unique_ptr<Sphere>& p_object)
{
    vec3d L = this->get_point_to_light_source_vector(point);
    double intensity_at_point;

    double diffuse_term = (normal * L) / (normal.magnitude() * L.magnitude());
    clamp_at_zero(diffuse_term);

    double specular_term = 0;
    if (!std::isnan(p_object->get_shininess()))  // if this object is somewhat shiny
    {
        vec3d R = reflect_ray(L, normal);  // "real" reflection vector (like a mirror)
        vec3d V = camera_pos - point;      // point -> camera

        specular_term = (R * V) / (R.magnitude() * V.magnitude());
        clamp_at_zero(specular_term);
        specular_term = std::pow(specular_term, p_object->get_shininess());
    }

    intensity_at_point = this->intensity * (diffuse_term + specular_term);
    return intensity_at_point;
}
