#pragma once
#include <memory>
#include "utils/vec/vec3.hpp"

class Sphere;

class LightSource
{
public:
    virtual ~LightSource() {};
    virtual double calculate_intensity(vec3d point, vec3d normal, vec3d camera_pos, std::unique_ptr<Sphere>& p_object) = 0;
    inline double get_intensity() { return intensity; }
protected:
    double intensity;
    double _calculate_intensity(vec3d point, vec3d L, vec3d normal,
                                vec3d camera_pos, std::unique_ptr<Sphere>& p_object);
};
