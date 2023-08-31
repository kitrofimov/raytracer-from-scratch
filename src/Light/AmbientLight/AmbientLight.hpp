#pragma once
#include "Light/Light.hpp"
#include "utils/vec/vec3.hpp"

class AmbientLight : public Light
{
public:
    AmbientLight(double intensity);
    double calculate_intensity(vec3d point, vec3d normal) override;
};
