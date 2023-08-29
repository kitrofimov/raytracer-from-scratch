#define SDL_MAIN_HANDLED
#include <iostream>
#include "utils/vec/vec2.hpp"
#include "Window/Window.hpp"

int main()
{
    Window window({512, 512});
    window.clear({0, 0, 0});

    unsigned int this_frame_time = 0;
    unsigned int delta_time = 0;
    unsigned int prev_frame_time = 0;

    while (window.is_running())
    {
        this_frame_time = SDL_GetTicks();
        delta_time = this_frame_time - prev_frame_time;

        window.poll_events();

        // window.clear({0, 0, 0});
        // std::cout << "Frametime: " << delta_time << std::endl;
        window.swap_buffers();

        prev_frame_time = this_frame_time;
    }

    return 0;
}
