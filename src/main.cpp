#define SDL_MAIN_HANDLED
#include <iostream>
#include "utils/vec/vec2.hpp"
#include "Window/Window.hpp"
#include "Camera/Camera.hpp"

int main()
{
    vec2i window_dimensions = {512, 512};
    Window window(window_dimensions);
    Camera camera({0, 0, 0}, {1, 1}, 1);
    window.clear({0, 0, 0});

    // For every pixel in the window
    for (int i = 0; i < window_dimensions.y; i++)
    {
        for (int j = 0; j < window_dimensions.x; j++)
        {
            vec2d ndc = window.pixel_to_ndc({j, i});
            vec3d point_on_projection_plane = window.ndc_to_projection_plane(ndc, &camera);
            vec3d ray_direction = point_on_projection_plane - camera->position;
            window.draw_pixel(ndc, {255, 0, 0, 255});
        }
    }

    unsigned int this_frame_time = 0;
    unsigned int delta_time = 0;
    unsigned int prev_frame_time = 0;

    while (window.is_running())
    {
        this_frame_time = SDL_GetTicks();
        delta_time = this_frame_time - prev_frame_time;

        window.poll_events();

        // window.clear({0, 0, 0});
        // Render calls

        // std::cout << "Frametime: " << delta_time << std::endl;
        window.swap_buffers();

        prev_frame_time = this_frame_time;
    }

    return 0;
}
