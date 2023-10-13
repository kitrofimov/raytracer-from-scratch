#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class AmbientLight : public LightSource
{
public:
    AmbientLight(double intensity, Color color);
    double calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                               std::unique_ptr<Sphere>& p_object) override;
    vec3d get_point_to_light_source_vector(vec3d& point) override;
    LightSourceType get_type() override;
};
