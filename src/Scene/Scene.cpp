#include <vector>
#include <cmath>
#include "Scene.hpp"
#include "utils/vec/vec3.hpp"

Scene::Scene(std::vector<std::unique_ptr<Object>> objects,
             std::vector<std::unique_ptr<Light>> lights) :
             objects(std::move(objects)),
             lights(std::move(lights))
{

}

color_t Scene::cast_ray(vec3d origin, vec3d direction)
{
    for (auto &p_object : this->objects)
    {
        vec3d CO = p_object->center - origin;
        double a = direction.dot_product(direction);
        double b = 2 * (CO.dot_product(direction));
        double c = CO.dot_product(CO) - (p_object->radius * p_object->radius);
        double D = b*b - 4.0*a*c;

        if (D >= 0)
            return p_object->color;
    }
    return {0, 0, 0, 255};
}
