#pragma once
#include "utils/vec/vec3.hpp"

class LightSource
{
public:
    virtual ~LightSource() {};
    virtual double calculate_intensity(vec3d point, vec3d normal) = 0;
    inline double get_intensity() { return intensity; }
protected:
    double intensity;
};
