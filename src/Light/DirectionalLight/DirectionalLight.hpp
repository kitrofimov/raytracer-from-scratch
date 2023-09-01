#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class DirectionalLight : public LightSource
{
public:
    DirectionalLight(double intensity, vec3d direction);
    double calculate_intensity(vec3d point, vec3d normal) override;
    inline vec3d get_direction() { return direction; }
private:
    vec3d direction;
};
