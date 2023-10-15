#include <memory>
#include "LightSource.hpp"
#include "Object/Object.hpp"
#include "utils/reflect_ray.hpp"

double LightSource::calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                                        std::unique_ptr<Object>& p_object)
{
    vec3d p2ls = this->get_point_to_light_source_vector(point);
    double intensity_at_point;

    double diffuse_term = (normal * p2ls) / (normal.magnitude() * p2ls.magnitude());
    diffuse_term = (diffuse_term < 0) ? 0 : diffuse_term;

    double specular_term = 0;
    if (!std::isnan(p_object->get_shininess()))  // if this object is somewhat shiny
    {
        vec3d reflection = reflect_ray(p2ls, normal);
        vec3d p2c = camera_pos - point;  // point -> camera

        specular_term = (reflection * p2c) / (reflection.magnitude() * p2c.magnitude());
        specular_term = (specular_term < 0) ? 0 : specular_term;
        specular_term = std::pow(specular_term, p_object->get_shininess());
    }

    intensity_at_point = this->intensity * (diffuse_term + specular_term);
    return intensity_at_point;
}
