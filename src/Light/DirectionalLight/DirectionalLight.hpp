#pragma once
#include "Light/Light.hpp"
#include "utils/vec/vec3.hpp"

class DirectionalLight : public Light
{
public:
    DirectionalLight(double intensity, vec3d position, vec3d direction);
    double calculate_intensity(vec3d point, vec3d normal) override;
    inline vec3d get_position() { return position; }
    inline vec3d get_direction() { return direction; }
private:
    vec3d position;
    vec3d direction;
};
