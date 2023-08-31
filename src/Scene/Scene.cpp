#include <vector>
#include <cmath>
#include "Scene.hpp"
#include "Sphere/Sphere.hpp"
#include "utils/vec/vec3.hpp"

Scene::Scene(std::vector<std::unique_ptr<Sphere>> objects)
{
    this->objects = std::move(objects);
}

color_t Scene::cast_ray(vec3d origin, vec3d direction)
{
    for (auto &p_object : this->objects)
    {
        vec3d CO = p_object->get_position() - origin;
        double a = direction.dot_product(direction);
        double b = 2 * (CO.dot_product(direction));
        double c = CO.dot_product(CO) - std::pow(p_object->get_radius(), 2);
        double D = b*b - 4.0*a*c;

        if (D >= 0)
            return p_object->get_color();
    }
    return {0, 0, 0, 255};
}
