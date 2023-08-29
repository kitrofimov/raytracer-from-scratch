#include "Camera.hpp"
#include "utils/vec/vec2.hpp"

Camera::Camera(vec3d position, vec2d projection_plane_dims, double d)
{
    this->position = position;
    this->projection_plane_dims = projection_plane_dims;
    this->d = d;
}
