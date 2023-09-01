#include <memory>
#include "LightSource.hpp"
#include "Sphere/Sphere.hpp"
#include "utils/clamp_at_zero.hpp"

// Internal function for calculating intensity of light at some point
// L is a vector (point -> light source)
double LightSource::_calculate_intensity(vec3d point, vec3d L, vec3d normal,
                                        vec3d camera_pos, std::unique_ptr<Sphere>& p_object)
{
    double intensity_at_point;

    double diffuse_term = normal.dot_product(L) / (normal.magnitude() * L.magnitude());
    clamp_at_zero(diffuse_term);

    double specular_term;
    if (!std::isnan(p_object->get_shininess()))  // if this object is somewhat shiny
    {
        // "real" reflection vector (assuming the surface is perfectly polished, like a mirror)
        vec3d R = normal * 2 * normal.dot_product(L) - L;
        vec3d V = camera_pos - point;  // point -> camera

        specular_term = R.dot_product(V) / (R.magnitude() * V.magnitude());
        clamp_at_zero(specular_term);
        specular_term = std::pow(specular_term, p_object->get_shininess());
    }

    intensity_at_point = this->intensity * (diffuse_term + specular_term);
    return intensity_at_point;
}
