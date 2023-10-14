#include <iostream>
#include <SDL2/SDL.h>
#include "utils/vec/vec2.hpp"
#include "SDLRenderer.hpp"
#include "Camera/Camera.hpp"
#include "constants.hpp"

SDLRenderer::SDLRenderer(vec2i dimensions)
{
    this->dimensions = dimensions;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialize SDL2 library: " << SDL_GetError() << std::endl;
	    std::exit(ERROR_CODE_SDL_INIT_FAIL);
    }
    SDL_CreateWindowAndRenderer(dimensions.x, dimensions.y, 0, &(this->sdl_window), &(this->sdl_renderer));
}

SDLRenderer::~SDLRenderer()
{
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    SDL_Quit();
}

void SDLRenderer::poll_events()
{
    while (SDL_PollEvent(&(this->sdl_event)))
    {
        if (sdl_event.type == SDL_QUIT || (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym == SDLK_ESCAPE))
            this->running = false;

        // if (sdl_event.type == SDL_KEYDOWN && sdl_event.key.repeat == 0) {}
    }
}

void SDLRenderer::swap_buffers()
{
    SDL_RenderPresent(this->sdl_renderer);
}

void SDLRenderer::draw_pixel(vec2i pos, Color c)
{
    SDL_SetRenderDrawColor(this->sdl_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(this->sdl_renderer, pos.x, pos.y);
}

void SDLRenderer::save_buffer(std::string filename)
{
    SDL_Surface* shot = SDL_CreateRGBSurface(0, this->dimensions.x, this->dimensions.y, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(this->sdl_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, shot->pixels, shot->pitch);
    filename += ".bmp";
    SDL_SaveBMP(shot, filename.c_str());
    SDL_FreeSurface(shot);
}
