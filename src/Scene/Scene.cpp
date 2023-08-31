#include <vector>
#include <cmath>
#include "Scene.hpp"
#include "Sphere/Sphere.hpp"
#include "utils/vec/vec3.hpp"

Scene::Scene(std::vector<std::unique_ptr<Sphere>> &objects,
             std::vector<std::unique_ptr<Light>> &light_sources)
{
    this->objects = std::move(objects);
    this->light_sources = std::move(light_sources);
}

// Cast the ray from camera (origin) to specified direction

// TODO: if there are more than one object the ray has intersection with,
// the one rendered is going to be not the one closer, but the one that
// is first in `objects` vector. need to fix this!

// TODO: remove magic number constant `1` in `if` statements!
color_t Scene::cast_ray(vec3d origin, vec3d direction)
{
    for (auto &p_object : this->objects)
    {
        // find the quadratic's discriminant
        vec3d CO = p_object->get_position() - origin;
        double a = direction.dot_product(direction);
        double b = 2 * (CO.dot_product(direction));
        double c = CO.dot_product(CO) - std::pow(p_object->get_radius(), 2);
        double D = b*b - 4.0*a*c;

        // solve the quadratic for the smallest POSITIVE root
        // (we don't need anything that is behind us!)
        double tm = (-b - std::sqrt(D)) / 2*a;
        double tp = (-b + std::sqrt(D)) / 2*a;
        double t;
        if (tm < tp)
        {
            if (tm > 1)
                t = tm;
            else  // behind the camera
                continue;
        }
        else  // (tp < tm)
        {
            if (tp > 1)
                t = tp;
            else  // behind the camera
                continue;
        }

        vec3d point = origin + direction * t;  // closest point of intersection
        vec3d normal = (point - p_object->get_position()).normalize();
        double light_intensity = this->calculate_light_intensity(point, normal);

        return p_object->get_color() * light_intensity;  // blend a color's object with light's intensity
    }
    return {0, 0, 0, 255};
}

// Calculate light intensity from all light sources at a given point with a given normal
double Scene::calculate_light_intensity(vec3d point, vec3d normal)
{
    double light_intensity = 0;
    for (auto &p_light_source : this->light_sources)
        light_intensity += p_light_source->calculate_intensity(point, normal);
    return light_intensity;
}
