#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class DirectionalLight : public LightSource
{
public:
    DirectionalLight(double intensity, color_t color, vec3d direction);
    double calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                               std::unique_ptr<Sphere>& p_object) override;
    inline vec3d get_direction() { return direction; }
private:
    vec3d direction;
};
