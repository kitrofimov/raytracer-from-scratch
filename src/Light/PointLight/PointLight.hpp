#pragma once
#include "Light/Light.hpp"
#include "utils/vec/vec3.hpp"

class PointLight : public Light
{
public:
    PointLight(double intensity, vec3d position);
    double calculate_intensity(vec3d point, vec3d normal) override;
    inline vec3d get_position() { return position; }
private:
    vec3d position;
};
