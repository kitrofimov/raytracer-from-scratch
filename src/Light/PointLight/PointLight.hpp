#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class PointLight : public LightSource
{
public:
    PointLight(double intensity, vec3d position);
    double calculate_intensity(vec3d point, vec3d normal) override;
    inline vec3d get_position() { return position; }
private:
    vec3d position;
};
