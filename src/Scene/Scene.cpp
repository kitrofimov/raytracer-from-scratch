#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Scene.hpp"
#include "Object/Object.hpp"
#include "Object/Sphere/Sphere.hpp"
#include "Object/Plane/Plane.hpp"
#include "Renderer/Renderer.hpp"
#include "Camera/Camera.hpp"

#include "utils/vec/vec.hpp"
#include "utils/exceptions.hpp"
#include "utils/quadratic.hpp"
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
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<LightSource>> light_sources;

    try
    {
        for (auto& object_data : scene_data["objects"])
            objects.emplace_back(this->create_primitive(object_data));

        for (auto& light_source_data : scene_data["light_sources"])
            light_sources.emplace_back(this->create_light_source(light_source_data));
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_CODE_JSON_UNKNOWN_TYPE);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected exception. This is a bug, please report it. Internal message:" << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(ERROR_CODE_JSON_UNKNOWN_EXCEPTION);
    }

    Color background_color = Color(std::vector<unsigned char>(scene_data["background_color"]));

    this->objects = std::move(objects);
    this->light_sources = std::move(light_sources);
    this->background_color = background_color;
}

Scene::Scene(std::vector<std::unique_ptr<Object>> &objects,
             std::vector<std::unique_ptr<LightSource>> &light_sources,
             Color background_color)
{
    this->objects = std::move(objects);
    this->light_sources = std::move(light_sources);
    this->background_color = background_color;
}

void Scene::render(std::unique_ptr<Renderer>& renderer, Camera& camera)
{
    vec2i dimensions = renderer->get_dimensions();
    for (int y = 0; y < dimensions.y; y++)
    {
        for (int x = 0; x < dimensions.x; x++)
        {
            vec2d ndc = renderer->pixel_to_ndc(vec2i(x, y));
            vec3d point_on_projection_plane = renderer->ndc_to_projection_plane(ndc, camera);
            vec3d ray_direction = (point_on_projection_plane - camera.get_position()).normalize();

            Color color = this->cast_ray(camera.get_position(), ray_direction, camera.get_position());
            renderer->draw_pixel(vec2i(x, y), color);
        }
    }
}

Color Scene::cast_ray(vec3d origin, vec3d direction, vec3d camera_pos, int r)
{
    if (r == CAST_RAY_RECURSIVE_LIMIT)  // recursion limit
        return Color(0, 0, 0, 0);

    std::map<double, Color> t_buffer;

    for (auto &p_object : this->objects)
    {
        double t = p_object->find_closest_intersection(origin, direction);
        if (std::isnan(t))
            continue;

        vec3d point = origin + direction * t;  // closest point of intersection
        vec3d normal = p_object->get_normal(point);

        double reflectiveness = p_object->get_reflectiveness();
        Color local_color;
        Color reflection_color;

        if (reflectiveness != 0)
        {
            vec3d reflection_direction = reflect_ray(-direction, normal);
            reflection_color = this->cast_ray(point, reflection_direction, camera_pos, r + 1);
        }
        if (reflectiveness != 1)
        {
            local_color = this->calculate_color(point, normal, camera_pos, p_object);
        }

        t_buffer[t] = lerp(local_color, reflection_color, reflectiveness);
    }

    // if no intersections with any objects
    if (t_buffer.size() == 0)
        return this->background_color;

    // there are some intersections, find the closest one
    return t_buffer[t_buffer.begin()->first];
}

Color Scene::calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                             std::unique_ptr<Object>& p_object)
{
    std::vector<Color> list;

    for (auto& p_light_source : this->light_sources)
    {
        if (!this->in_shadow(point, p_light_source))
        {
            double intensity = p_light_source->calculate_intensity(point, normal, camera_pos, p_object);
            // clamp intensity to remove visible "light borders" with ambient and regular light sources
            intensity = (intensity < 0.2) ? 0.2 : intensity;
            list.push_back(
                Color::mix({p_light_source->get_color(), p_object->get_color()}) * \
                intensity
            );
        }
    }

    return Color::mix(list);
}

bool Scene::in_shadow(vec3d& point, std::unique_ptr<LightSource>& p_light_source)
{
    if (p_light_source->get_type() == LightSourceType::AmbientLight)
    {
        return false;
    }

    vec3d p2ls = p_light_source->get_point_to_light_source_vector(point).normalize();

    for (auto& p_object : this->objects)
    {
        double t = p_object->find_closest_intersection(point, p2ls);
        // if it is PointLight and distance to intersection is further away from light source,
        // then it is not in shadow
        if ((p_light_source->get_type() == LightSourceType::PointLight) && (t >= 1))
            continue;
        if (!std::isnan(t) && t > 0.1)  // if there is an intersection
            return true;
    }
    return false;
}

std::unique_ptr<Object> Scene::create_primitive(json data)
{
    Color color = Color(std::vector<unsigned char>(data["color"]));
    double shininess;
    if (data["shininess"].is_string())
        shininess = qNaN;
    else
        shininess = double(data["shininess"]);
    double reflectiveness = double(data["reflectiveness"]);

    if (data["type"] == "Sphere")
    {
        vec3d position = vec3d(std::vector<double>(data["position"]));
        double radius = double(data["radius"]);
        return std::make_unique<Sphere>(color, shininess, reflectiveness, position, radius);
    }
    else if (data["type"] == "Plane")
    {
        vec3d normal = vec3d(std::vector<double>(data["normal"]));
        vec3d point = vec3d(std::vector<double>(data["point"]));
        return std::make_unique<Plane>(color, shininess, reflectiveness, point, normal);
    }

    throw std::invalid_argument("Unknown object (primitive) type: " + std::string(data["type"]));
}

std::unique_ptr<LightSource> Scene::create_light_source(json data)
{
    double intensity = double(data["intensity"]);
    Color color = Color(std::vector<unsigned char>(data["color"]));

    if (data["type"] == "AmbientLight")
    {
        return std::make_unique<AmbientLight>(intensity, color);
    }
    else if (data["type"] == "DirectionalLight")
    {
        vec3d direction = vec3d(std::vector<double>(data["direction"]));
        return std::make_unique<DirectionalLight>(intensity, color, direction);
    }
    else if (data["type"] == "PointLight")
    {
        vec3d position = vec3d(std::vector<double>(data["position"]));
        return std::make_unique<PointLight>(intensity, color, position);
    }

    throw std::invalid_argument("Unknown light source type: " + std::string(data["type"]));
}
