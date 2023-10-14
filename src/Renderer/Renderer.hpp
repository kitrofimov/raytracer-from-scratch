#pragma once
#include "utils/Color/Color.hpp"
#include "utils/vec/vec.hpp"

class Camera;

class Renderer
{
public:
    virtual ~Renderer() {};

    vec2d pixel_to_ndc(vec2i position);
    vec3d ndc_to_projection_plane(vec2d ndc, Camera& camera);

    virtual void poll_events() = 0;
    virtual void swap_buffers() = 0;
    virtual void draw_pixel(vec2i pos, Color c) = 0;
    virtual void save_buffer(std::string filename) = 0;

    inline bool is_running() { return running; }
    inline vec2i get_dimensions() { return dimensions; }

protected:
    bool running = true;
    vec2i dimensions;
};
