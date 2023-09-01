#pragma once
#include "utils/vec/vec2.hpp"

class Camera
{
public:
    Camera(vec3d position, vec2d projection_plane_dims, double d);
    inline vec3d get_position() { return position; }
    inline vec2d get_projection_plane_dims() { return projection_plane_dims; }
    inline double get_d() { return d; }
private:
    vec3d position;
    vec2d projection_plane_dims;
    double d;
};
