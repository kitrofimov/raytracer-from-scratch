#pragma once
#include <SDL2/SDL.h>
#include "Renderer/Renderer.hpp"
#include "Camera/Camera.hpp"
#include "utils/vec/vec2.hpp"
#include "utils/color/color.hpp"

class Window : public Renderer
{
public:
    Window(vec2i dimensions);
    ~Window() override;

    void poll_events() override;
    void swap_buffers() override;
    void draw_pixel(vec2i pos, Color c) override;

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_Event sdl_event;
};
