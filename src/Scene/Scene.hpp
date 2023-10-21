#pragma once

#include <vector>
#include <memory>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "Object/Object.hpp"
#include "Object/Sphere/Sphere.hpp"
#include "Light/Light.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

using json = nlohmann::json;

class Renderer;
class SDLRenderer;
class TerminalRenderer;
class Camera;

class Scene
{
public:
    // Parse the scene form a JSON file
    Scene(std::filesystem::path scene_file_path);

    Scene(std::vector<std::unique_ptr<Object>> &objects,
          std::vector<std::unique_ptr<LightSource>> &light_sources,
          Color background_color = Color(0, 0, 0, 255));

    // Render the scene
    void render(std::unique_ptr<Renderer>& renderer, Camera& camera);

    // Cast the ray from origin to specified direction, return the color in this direction
    // `r` - recursive parameter, only used internally by recursion
    Color cast_ray(vec3d origin, vec3d direction, vec3d camera_pos, int r = 0);

    // Calculate light intensity from all light sources at a given point with a given normal
    Color calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                            std::unique_ptr<Object>& p_object);

    // Determine whether or not given `point` is in shadow from given `p_light_source`
    bool in_shadow(vec3d& point, std::unique_ptr<LightSource>& p_light_source);

private:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<LightSource>> light_sources;
    Color background_color;

    // Internal functions that help to parse objects from JSON (file path constructor)
    static std::unique_ptr<Object> create_primitive(json data);
    static std::unique_ptr<LightSource> create_light_source(json data);
};
