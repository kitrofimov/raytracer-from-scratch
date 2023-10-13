#include "Camera.hpp"
#include "utils/vec/vec.hpp"

Camera::Camera(vec3d position, vec2d projection_plane_dims, double near_plane_distance)
{
    this->position = position;
    this->projection_plane_dims = projection_plane_dims;
    this->near_plane_distance = near_plane_distance;
}
