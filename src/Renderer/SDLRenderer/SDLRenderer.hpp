#pragma once
#include <SDL2/SDL.h>
#include "Renderer/Renderer.hpp"
#include "Camera/Camera.hpp"
#include "utils/vec/vec2.hpp"
#include "utils/color/color.hpp"

class SDLRenderer : public Renderer
{
public:
    SDLRenderer(vec2i dimensions);
    ~SDLRenderer() override;

    void poll_events() override;
    void swap_buffers() override;
    void draw_pixel(vec2i pos, Color c) override;
    virtual void save_buffer(std::string filename) override;

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_Event sdl_event;
};
