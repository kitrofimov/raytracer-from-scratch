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
                shininess = qNaN;
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
color_t Scene::cast_ray(vec3d camera_pos, vec3d direction)
{
    std::map<double, color_t> t_buffer;

    for (auto &p_object : this->objects)
    {
        double t = this->find_closest_intersection(camera_pos, direction, p_object);
        if (std::isnan(t))  // if no suitable intersections
            continue;

        vec3d point = camera_pos + direction * t;  // closest point of intersection
        vec3d normal = (point - p_object->get_position()).normalize();

        t_buffer[t] = this->calculate_color(point, normal, camera_pos, p_object);
    }

    // if no intersections at all
    if (t_buffer.size() == 0)
        return this->background_color;

    // there are some intersections (maybe multiple of them, so find the closest one)
    return t_buffer[t_buffer.begin()->first];
}

// Solve a quadratic to find distance to closest intersection with an object (Sphere)
// Returns quiet NaN to show that there is no intersections at all or they are behind the camera
// Ignores t = 0!!!
double Scene::find_closest_intersection(vec3d& point, vec3d& direction, std::unique_ptr<Sphere>& p_object)
{
    // find the discriminant
    vec3d CO = point - p_object->get_position();  // sphere's center -> point
    double a = direction * direction;
    double b = 2 * (CO * direction);
    double c = (CO * CO) - std::pow(p_object->get_radius(), 2);
    double D = b*b - 4.0*a*c;

    if (D < 0) return qNaN;  // no intersections at all

    // solve the quadratic for the smallest POSITIVE root
    // (we don't need anything that is behind us!)
    double t = (-b - std::sqrt(D)) / 2*a;
    if (t > 0)
        return t;
    else if (t == 0)  // if intersection is this point, then compute other root
    {
        t = (-b + std::sqrt(D)) / 2*a;
        if (t == 0)  // if it is still 0 (D == 0), then return qNaN
            return qNaN;
    }
    else  // intersection is behind (t < 0)
        return qNaN;
    return;
}

// Calculate light intensity from all light sources at a given point with a given normal
color_t Scene::calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                               std::unique_ptr<Sphere>& p_object)
{
    std::vector<color_t> list;

    for (auto& p_light_source : this->light_sources)
    {
        if (!this->in_shadow(point, p_light_source))
        {
            list.push_back(
                color_t::mix({p_light_source->get_color(), p_object->get_color()}) * \
                p_light_source->calculate_intensity(point, normal, camera_pos, p_object)
            );
        }
    }

    return color_t::mix(list);
}

// Determine whether or not given `point` is in shadow from given `p_light_source`
bool Scene::in_shadow(vec3d& point, std::unique_ptr<LightSource>& p_light_source)
{
    vec3d L = p_light_source->get_point_to_light_source_vector(point);
    if (L == vec3d(0, 0, 0))  // if ambient light
    {
        return false;
    }
    else
    {
        for (auto& p_object : this->objects)
        {
            double t = this->find_closest_intersection(point, L, p_object);
            if (!std::isnan(t))
                return true;
        }
        return false;
    }
}
