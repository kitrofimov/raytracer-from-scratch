#pragma once
#include <memory>
#include "utils/vec/vec3.hpp"
#include "utils/color/color.hpp"

class Sphere;

enum class LightSourceType
{
    AmbientLight,
    DirectionalLight,
    PointLight
};

class LightSource
{
public:
    virtual ~LightSource() {};

    // Calculate point color considering *only* this light source
    // This function is virtual because `AmbientLight` must overload it
    virtual double calculate_intensity(vec3d& point, vec3d& normal, vec3d& camera_pos,
                                       std::unique_ptr<Sphere>& p_object);

    virtual vec3d get_point_to_light_source_vector(vec3d& point) = 0;
    virtual LightSourceType get_type() = 0;
    inline double get_intensity() { return intensity; }
    inline Color get_color() { return color; }
protected:
    double intensity;
    Color color;
};
