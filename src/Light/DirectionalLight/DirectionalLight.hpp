#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class DirectionalLight : public LightSource
{
public:
    DirectionalLight(double intensity, color_t color, vec3d direction);
    vec3d get_point_to_light_source_vector(vec3d& point) override;
    LightSourceType get_type() override;
    inline vec3d get_direction() { return direction; }
private:
    vec3d direction;
};
