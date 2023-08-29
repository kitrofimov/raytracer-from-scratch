#pragma once
#include "utils/vec/vec2.hpp"

class Camera
{
public:
    Camera(vec3d position, vec2d projection_plane_dims, double d);

    vec3d position;
    vec2d projection_plane_dims = {1, 1};
    double d = 1;
};
