#include <memory>
#include "LightSource.hpp"
#include "Sphere/Sphere.hpp"
#include "utils/clamp_at_zero.hpp"

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
        // "real" reflection vector (assuming the surface is perfectly polished, like a mirror)
        vec3d R = normal * 2 * (normal * L) - L;
        vec3d V = camera_pos - point;  // point -> camera

        specular_term = (R * V) / (R.magnitude() * V.magnitude());
        clamp_at_zero(specular_term);
        specular_term = std::pow(specular_term, p_object->get_shininess());
    }

    intensity_at_point = this->intensity * (diffuse_term + specular_term);
    return intensity_at_point;
}
