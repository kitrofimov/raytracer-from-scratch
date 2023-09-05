#include "Camera.hpp"
#include "utils/vec/vec.hpp"

Camera::Camera(vec3d position, vec2d projection_plane_dims, double near_plane)
{
    this->position = position;
    this->projection_plane_dims = projection_plane_dims;
    this->near_plane = near_plane;
}
