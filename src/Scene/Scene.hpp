#pragma once
#include <vector>
#include <memory>
#include <filesystem>
#include "Sphere/Sphere.hpp"
#include "Light/Light.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

class Window;
class Camera;

class Scene
{
public:
    Scene(std::filesystem::path scene_file_path);
    Scene(std::vector<std::unique_ptr<Sphere>> &objects,
          std::vector<std::unique_ptr<LightSource>> &light_sources,
          color_t background_color = color_t(0, 0, 0, 255));

    void render(Window& window, Camera& camera);
    color_t cast_ray(vec3d camera_pos, vec3d direction);
    double find_closest_intersection(vec3d& point, vec3d& direction, std::unique_ptr<Sphere>& p_object);
    color_t calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                            std::unique_ptr<Sphere>& p_object);
    bool in_shadow(vec3d& point, std::unique_ptr<LightSource>& p_light_source);
private:
    std::vector<std::unique_ptr<Sphere>> objects;
    std::vector<std::unique_ptr<LightSource>> light_sources;
    color_t background_color;
};
