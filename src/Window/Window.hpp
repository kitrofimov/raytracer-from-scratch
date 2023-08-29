#pragma once
#include <SDL2/SDL.h>
#include "Camera/Camera.hpp"
#include "utils/vec/vec2.hpp"
#include "utils/color/color.hpp"

class Window
{
public:
    Window(vec2i actual_dimensions);
    ~Window();

    void poll_events();
    void clear(color_t c);
    void swap_buffers();
    bool is_running();

    vec2d pixel_to_ndc(vec2i position);
    vec3d ndc_to_projection_plane(vec2d ndc, Camera *camera);

    void draw_pixel(vec2d ndc, color_t c);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_Event sdl_event;

    bool running = true;
    vec2i dimensions;
};
