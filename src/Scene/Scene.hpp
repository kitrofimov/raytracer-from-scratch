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
    // Parse the scene form a JSON file
    Scene(std::filesystem::path scene_file_path);

    Scene(std::vector<std::unique_ptr<Sphere>> &objects,
          std::vector<std::unique_ptr<LightSource>> &light_sources,
          Color background_color = Color(0, 0, 0, 255));

    // Render the scene
    void render(Window& window, Camera& camera);

    // Cast the ray from origin to specified direction
    // `r` - recursive parameter, only used internally by recursion
    Color cast_ray(vec3d origin, vec3d direction, int r = 0);

    // Find a distance to closest intersection with an object (Sphere)
    // Returns quiet NaN to show that there is no intersections at all or they are behind the camera
    // Ignores t = 0 (does not count `point` itself as intersection)
    double find_closest_intersection(vec3d& point, vec3d& direction, std::unique_ptr<Sphere>& p_object);

    // Calculate light intensity from all light sources at a given point with a given normal
    Color calculate_color(vec3d& point, vec3d& normal, vec3d& camera_pos,
                            std::unique_ptr<Sphere>& p_object);

    // Determine whether or not given `point` is in shadow from given `p_light_source`
    bool in_shadow(vec3d& point, std::unique_ptr<LightSource>& p_light_source);

private:
    std::vector<std::unique_ptr<Sphere>> objects;
    std::vector<std::unique_ptr<LightSource>> light_sources;
    Color background_color;
};
