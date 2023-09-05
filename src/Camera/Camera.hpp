#pragma once
#include "utils/vec/vec.hpp"

class Camera
{
public:
    Camera(vec3d position, vec2d projection_plane_dims, double near_plane);
    inline vec3d get_position() { return position; }
    inline vec2d get_projection_plane_dims() { return projection_plane_dims; }
    inline double get_near_plane() { return near_plane; }
private:
    vec3d position;
    vec2d projection_plane_dims;
    double near_plane;
};
