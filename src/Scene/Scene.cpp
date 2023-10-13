#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Scene.hpp"
#include "Sphere/Sphere.hpp"
#include "Window/Window.hpp"
#include "Camera/Camera.hpp"

#include "utils/vec/vec.hpp"
#include "utils/exceptions.hpp"
#include "utils/solve_quadratic.hpp"
#include "utils/smallest_positive_in_container.hpp"
#include "utils/reflect_ray.hpp"
#include "utils/lerp.hpp"
#include "constants.hpp"

using json = nlohmann::json;

Scene::Scene(std::filesystem::path scene_file_path)
{
    // Read the file, parse JSON
    json scene_data;
    try
    {
        std::ifstream f;
        f.exceptions(std::ifstream::failbit);
        f.open(scene_file_path);
        scene_data = json::parse(f);
        f.close();
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << "Failed to open " << scene_file_path << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_CODE_FILE_EXCEPTION);
    }
    catch (const json::parse_error& e)
    {
        std::cerr << "JSON parse error" << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_CODE_JSON_PARSE);
    }

    // Parse objects
    std::vector<std::unique_ptr<Sphere>> objects;
    std::vector<std::unique_ptr<LightSource>> light_sources;
    try
    {
        for (auto& object : scene_data["objects"])
        {
            std::string type = object["type"];

            if (type == "Sphere")
            {
                vec3d position = vec3d(std::vector<double>(object["position"]));
                double radius = object["radius"];
                color_t color = color_t(std::vector<unsigned char>(object["color"]));
                double shininess;
                double reflectiveness = object["reflectiveness"];

                try  // if double
                {
                    shininess = object["shininess"];
                }
                catch (const json::type_error& e)  // if NaN (string)
                {
                    shininess = qNaN;
                }

                objects.emplace_back(std::make_unique<Sphere>(
                    position,
                    radius,
                    color,
                    shininess,
                    reflectiveness
                ));
            }

            else
            {
                throw JSONFormatError("Bad JSON format: there is no " + type + " object type");
            }
    }

        // Parse light sources
        for (auto& light_source : scene_data["light_sources"])
        {
            std::string type = light_source["type"];
            double intensity = light_source["intensity"];
            color_t color = color_t(std::vector<unsigned char>(light_source["color"]));

            if (type == "AmbientLight")
            {
                light_sources.emplace_back(std::make_unique<AmbientLight>(
                    intensity,
                    color
                ));
            }

            else if (type == "PointLight")
            {
                vec3d position = vec3d(std::vector<double>(light_source["position"]));
                light_sources.emplace_back(std::make_unique<PointLight>(
                    intensity,
                    color,
                    position
                ));
            }

            else if (type == "DirectionalLight")
            {
                vec3d direction = vec3d(std::vector<double>(light_source["direction"]));
                light_sources.emplace_back(std::make_unique<DirectionalLight>(
                    intensity,
                    color,
                    direction
                ));
            }

            else
            {
                throw JSONFormatError("Bad JSON format: there is no " + type + " light type");
            }
        }
    }
    catch (const JSONFormatError& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_CODE_JSON_FORMAT);
    }
    catch (const json::type_error& e)
    {
        std::cerr << "JSONFormatError\nMake sure you have valid scene file\nInternal error message:" << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_CODE_JSON_FORMAT);
    }

    color_t background_color = color_t(std::vector<unsigned char>(scene_data["background_color"]));

    this->objects = std::move(objects);
    this->light_sources = std::move(light_sources);
    this->background_color = background_color;
}

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
    for (int y = 0; y < window.get_dimensions().y; y++)
    {
        for (int x = 0; x < window.get_dimensions().x; x++)
        {
            vec2d ndc = window.pixel_to_ndc(vec2i(x, y));
            vec3d point_on_projection_plane = window.ndc_to_projection_plane(ndc, camera);
            vec3d ray_direction = (point_on_projection_plane - camera.get_position()).normalize();

            color_t color = this->cast_ray(camera.get_position(), ray_direction);
            window.draw_pixel(vec2i(x, y), color);
        }
    }
}

color_t Scene::cast_ray(vec3d origin, vec3d direction, int r)
{
    if (r == CAST_RAY_RECURSIVE_LIMIT)  // recursion limit
        return color_t(0, 0, 0, 0);

    std::map<double, color_t> t_buffer;

    for (auto &p_object : this->objects)
    {
        double t = this->find_closest_intersection(origin, direction, p_object);
        if (std::isnan(t))
            continue;

        vec3d point = origin + direction * t;  // closest point of intersection
        vec3d normal = (point - p_object->get_position()).normalize();

        double reflectiveness = p_object->get_reflectiveness();
        color_t local_color;
        color_t reflection_color;

        if (reflectiveness != 0)
        {
            vec3d reflection_direction = reflect_ray(-direction, normal);
            reflection_color = this->cast_ray(point, reflection_direction, r + 1);
        }
        if (reflectiveness != 1)
        {
            local_color = this->calculate_color(point, normal, origin, p_object);
        }

        t_buffer[t] = lerp(local_color, reflection_color, reflectiveness);
    }

    // if no intersections with any objects
    if (t_buffer.size() == 0)
        return this->background_color;

    // there are some intersections, find the closest one
    return t_buffer[t_buffer.begin()->first];
}

double Scene::find_closest_intersection(vec3d& point, vec3d& direction, std::unique_ptr<Sphere>& p_object)
{
    vec3d c2p = point - p_object->get_position();  // sphere's center -> point
    double a = direction * direction;
    double b = 2 * (c2p * direction);
    double c = (c2p * c2p) - std::pow(p_object->get_radius(), 2);

    auto distances = solve_quadratic(a, b, c);
    double t = smallest_positive_in_container(distances);
    return t;
}

color_t Scene::calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                               std::unique_ptr<Sphere>& p_object)
{
    std::vector<color_t> list;

    for (auto& p_light_source : this->light_sources)
    {
        if (!this->in_shadow(point, p_light_source))
        {
            double intensity = p_light_source->calculate_intensity(point, normal, camera_pos, p_object);
            // clamp intensity to remove visible "light borders" with ambient and regular light sources
            intensity = (intensity < 0.2) ? 0.2 : intensity;
            list.push_back(
                color_t::mix({p_light_source->get_color(), p_object->get_color()}) * \
                intensity
            );
        }
    }

    return color_t::mix(list);
}

bool Scene::in_shadow(vec3d& point, std::unique_ptr<LightSource>& p_light_source)
{
    if (p_light_source->get_type() == LightSourceType::AmbientLight)
    {
        return false;
    }

    vec3d L = p_light_source->get_point_to_light_source_vector(point).normalize();

    for (auto& p_object : this->objects)
    {
        double t = this->find_closest_intersection(point, L, p_object);
        // if it is PointLight and distance to intersection is further away from light source,
        // then it is not in shadow
        if ((p_light_source->get_type() == LightSourceType::PointLight) && (t >= 1))
            continue;
        if (!std::isnan(t) && t > 0.1)  // if there is an intersection
            return true;
    }
    return false;
}
