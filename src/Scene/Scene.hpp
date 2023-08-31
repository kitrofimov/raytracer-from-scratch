#pragma once
#include <vector>
#include <memory>
#include "Sphere/Sphere.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

class Scene
{
public:
    Scene(std::vector<std::unique_ptr<Sphere>> objects);
    color_t cast_ray(vec3d origin, vec3d direction);
private:
    std::vector<std::unique_ptr<Sphere>> objects;
};
