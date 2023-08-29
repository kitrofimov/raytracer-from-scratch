#include <iostream>
#include <SDL2/SDL.h>
#include "utils/vec/vec2.hpp"
#include "Window.hpp"
#include "constants.hpp"

Window::Window(vec2i dimensions)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL2 library: " << SDL_GetError() << std::endl;
	    std::exit(SDL2_INIT_FAIL_EXIT_CODE);
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

void Window::clear(color_t c)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(this->sdl_renderer);
}

void Window::draw_pixel(vec2i position, color_t c)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(this->sdl_renderer, position.x, position.y);
}

void Window::swap_buffers()
{
    SDL_RenderPresent(this->sdl_renderer);
}

bool Window::is_running()
{
    return this->running;
}
