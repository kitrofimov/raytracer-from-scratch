#pragma once
#include "Light/LightSource.hpp"
#include "utils/vec/vec3.hpp"

class AmbientLight : public LightSource
{
public:
    AmbientLight(double intensity);
    double calculate_intensity(vec3d point, vec3d normal) override;
};
