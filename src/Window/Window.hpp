#pragma once
#include <SDL2/SDL.h>
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

    void draw_pixel(vec2i position, color_t c);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_Event sdl_event;

    bool running = true;
};
