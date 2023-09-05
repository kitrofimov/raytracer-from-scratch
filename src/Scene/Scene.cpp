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
#include "constants.hpp"

using json = nlohmann::json;

// Parse the scene form a JSON file
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
        std::cerr << "Failed to open " << scene_file_path.c_str() << std::endl;
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
    for (auto& object : scene_data["objects"])
    {
        std::string type = object["type"];

        if (type == "Sphere")
        {
            vec3d position = vec3d(std::vector<double>(object["position"]));
            double radius = object["radius"];
            color_t color = color_t(std::vector<unsigned char>(object["color"]));
            double shininess;

            try  // if double
            {
                shininess = object["shininess"];
            }
            catch (const json::type_error& e)  // if NaN (string)
            {
                shininess = std::numeric_limits<double>::quiet_NaN();
            }

            objects.emplace_back(std::make_unique<Sphere>(
                position,
                radius,
                color,
                shininess
            ));
        }

        else
        {
            throw JSONFormatError("Bad JSON format: there is no " + type + " object type");
        }
    }

    // Parse light sources
    std::vector<std::unique_ptr<LightSource>> light_sources;
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
            throw JSONFormatError("Bad JSON format: there is no " + type + " light source type");
        }
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
    // For every pixel in the window
    for (int y = 0; y < window.get_dimensions().y; y++)
    {
        for (int x = 0; x < window.get_dimensions().x; x++)
        {
            vec2d ndc = window.pixel_to_ndc(vec2i(x, y));
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
        double a = direction * direction;
        double b = -2 * (CO * direction);
        double c = (CO * CO) - std::pow(p_object->get_radius(), 2);
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
    std::vector<color_t> list(this->light_sources.size());

    std::size_t i = 0;
    for (; i < this->light_sources.size(); i++)
    {
        auto& p_light_source = this->light_sources[i];
        list[i] = color_t::mix({p_light_source->get_color(), p_object->get_color()}) * \
                  p_light_source->calculate_intensity(point, normal, camera_pos, p_object);
    }

    return color_t::mix(list);
}
