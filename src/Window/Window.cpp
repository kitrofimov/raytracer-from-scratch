#include <iostream>
#include <SDL2/SDL.h>
#include "utils/vec/vec2.hpp"
#include "Window.hpp"
#include "Camera/Camera.hpp"
#include "constants.hpp"

Window::Window(vec2i dimensions)
{
    this->dimensions = dimensions;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL2 library: " << SDL_GetError() << std::endl;
	    std::exit(ERROR_CODE_SDL_INIT_FAIL);
    }
    SDL_CreateWindowAndRenderer(dimensions.x, dimensions.y, 0, &(this->sdl_window), &(this->sdl_renderer));
}

Window::~Window()
{
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    SDL_Quit();
}

void Window::poll_events()
{
    while (SDL_PollEvent(&(this->sdl_event)))
    {
        if (sdl_event.type == SDL_QUIT || (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym == SDLK_ESCAPE))
            this->running = false;

        // if (sdl_event.type == SDL_KEYDOWN && sdl_event.key.repeat == 0) {}
    }
}

void Window::clear(Color c)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(this->sdl_renderer);
}

void Window::swap_buffers()
{
    SDL_RenderPresent(this->sdl_renderer);
}

vec2d Window::pixel_to_ndc(vec2i position)
{
    return vec2d(
        (double) position.x / this->dimensions.x * 2 - 1,
        (double) position.y / this->dimensions.y * 2 - 1
    );
}

vec3d Window::ndc_to_projection_plane(vec2d ndc, Camera& camera)
{
    return vec3d(
        -ndc.x * camera.get_projection_plane_dims().x,
        -ndc.y * camera.get_projection_plane_dims().y,
        camera.get_near_plane_distance()
    );
}

void Window::draw_pixel(vec2i pos, Color c)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(this->sdl_renderer, pos.x, pos.y);
}
