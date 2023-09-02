#define SDL_MAIN_HANDLED
#include <iostream>

#include "Window/Window.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"

#include "Sphere/Sphere.hpp"

#include "Light/Light.hpp"
#include "utils/vec/vec.hpp"

int main()
{
    // Initialization
    vec2i window_dimensions = {512, 512};
    Window window(window_dimensions);
    Camera camera({0, 0, 0}, {1, 1}, 1.5);
    window.clear({0, 0, 0});

    // Scene creation
    std::vector<std::unique_ptr<Sphere>> objects;
    objects.emplace_back(std::make_unique<Sphere>(
        (vec3d) {0, 0, 2},
        1,
        (color_t) {0, 155, 0, 255}
    ));

    std::vector<std::unique_ptr<LightSource>> light_sources;
    light_sources.emplace_back(std::make_unique<DirectionalLight>(
        1.0,
        (color_t) {255, 0, 255, 255},
        (vec3d) {1, -1, 1}
    ));
    // light_sources.emplace_back(std::make_unique<PointLight>(
    //     1.0,
    //     (color_t) {255, 255, 255, 255},
    //     (vec3d) {-2, -1, -1}
    // ));
    // light_sources.emplace_back(std::make_unique<AmbientLight>(
    //     0.1,
    //     (color_t) {255, 255, 255, 255}
    // ));

    Scene scene(objects, light_sources);

    // For every pixel in the window
    for (int y = 0; y < window_dimensions.y; y++)
    {
        for (int x = 0; x < window_dimensions.x; x++)
        {
            vec2d ndc = window.pixel_to_ndc({x, y});
            vec3d point_on_projection_plane = window.ndc_to_projection_plane(ndc, camera);
            vec3d ray_direction = (point_on_projection_plane - camera.get_position()).normalize();

            color_t color = scene.cast_ray(camera.get_position(), ray_direction);
            window.draw_pixel(ndc, color);
        }
    }

    std::cout << "Rendered!" << std::endl;

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
