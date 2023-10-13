#pragma once
#include "utils/vec/vec.hpp"

class Camera
{
public:
    Camera(vec3d position, vec2d projection_plane_dims, double near_plane_distance);
    inline vec3d get_position() { return position; }
    inline vec2d get_projection_plane_dims() { return projection_plane_dims; }
    inline double get_near_plane_distance() { return near_plane_distance; }
private:
    vec3d position;
    vec2d projection_plane_dims;
    double near_plane_distance;
};
