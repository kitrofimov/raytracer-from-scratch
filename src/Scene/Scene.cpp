#include <vector>
#include <cmath>
#include "Scene.hpp"
#include "Sphere/Sphere.hpp"
#include "Window/Window.hpp"
#include "Camera/Camera.hpp"
#include "utils/vec/vec.hpp"

Scene::Scene(std::vector<std::unique_ptr<Sphere>> &objects,
             std::vector<std::unique_ptr<LightSource>> &light_sources,
             color_t background_color)
{
    this->objects = std::move(objects);
    this->light_sources = std::move(light_sources);
    this->background_color = background_color;
}

void Scene::render(Window& window, Camera& camera)
{
    // For every pixel in the window
    for (int y = 0; y < window.get_dimensions().y; y++)
    {
        for (int x = 0; x < window.get_dimensions().x; x++)
        {
            vec2d ndc = window.pixel_to_ndc({x, y});
            vec3d point_on_projection_plane = window.ndc_to_projection_plane(ndc, camera);
            vec3d ray_direction = (point_on_projection_plane - camera.get_position()).normalize();

            color_t color = this->cast_ray(camera.get_position(), ray_direction);
            window.draw_pixel(ndc, color);
        }
    }
}

// Cast the ray from camera (origin) to specified direction
//     TODO: if there are more than one object the ray has intersection
// with, the one rendered is going to be not the one closer, but the one
// that is first in `objects` vector. need to fix this! (some z-buffer?)
//     TODO: remove magic number constant `1` in `if` statements! (that
// is near plane distance)
color_t Scene::cast_ray(vec3d camera_pos, vec3d direction)
{
    for (auto &p_object : this->objects)
    {
        // find the quadratic's discriminant
        vec3d CO = p_object->get_position() - camera_pos;  // sphere's center -> camera
        double a = direction.dot_product(direction);
        double b = -2 * (CO.dot_product(direction));
        double c = CO.dot_product(CO) - std::pow(p_object->get_radius(), 2);
        double D = b*b - 4.0*a*c;

        if (D < 0) continue;  // no intersections at all

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

        vec3d point = camera_pos + direction * t;  // closest point of intersection
        vec3d normal = (point - p_object->get_position()).normalize();

        return this->calculate_color(point, normal, camera_pos, p_object);
    }
    return this->background_color;
}

// Calculate light intensity from all light sources at a given point with a given normal
color_t Scene::calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                               std::unique_ptr<Sphere>& p_object)
{
    // TODO: bugged code! need to find a way to blend light color with object color
    // ONLY IF there ARE some light. if no light - I want it to be completely black.

    std::vector<color_t> list(this->light_sources.size() + 1);

    std::size_t i = 0;
    for (; i < this->light_sources.size(); i++)
    {
        auto& p_light_source = this->light_sources[i];
        list[i] = p_light_source->get_color() * \
                  p_light_source->calculate_intensity(point, normal, camera_pos, p_object);
    }
    list[i] = p_object->get_color();

    return color_t::mix(list);
}
