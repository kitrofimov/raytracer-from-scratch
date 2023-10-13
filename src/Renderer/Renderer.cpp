#include "Camera/Camera.hpp"
#include "Renderer.hpp"
#include "utils/vec/vec2.hpp"

vec2d Renderer::pixel_to_ndc(vec2i position)
{
    return vec2d(
        (double) position.x / this->dimensions.x * 2 - 1,
        (double) position.y / this->dimensions.y * 2 - 1
    );
}

vec3d Renderer::ndc_to_projection_plane(vec2d ndc, Camera& camera)
{
    return vec3d(
        -ndc.x * camera.get_projection_plane_dims().x,
        -ndc.y * camera.get_projection_plane_dims().y,
        camera.get_near_plane_distance()
    );
}
