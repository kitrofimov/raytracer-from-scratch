#pragma once
#include <vector>
#include <memory>
#include "Sphere/Sphere.hpp"
#include "Light/Light.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

class Scene
{
public:
    Scene(std::vector<std::unique_ptr<Sphere>> &objects,
          std::vector<std::unique_ptr<Light>> &light_sources);
    color_t cast_ray(vec3d origin, vec3d direction);
    double calculate_light_intensity(vec3d point, vec3d normal);
private:
    std::vector<std::unique_ptr<Sphere>> objects;
    std::vector<std::unique_ptr<Light>> light_sources;
};
