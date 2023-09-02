#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class AmbientLight : public LightSource
{
public:
    AmbientLight(double intensity, color_t color);
    double calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                               std::unique_ptr<Sphere>& p_object) override;
};
