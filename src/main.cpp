#define SDL_MAIN_HANDLED
#include <iostream>

// #include "Window/Window.hpp"
// #include "Camera/Camera.hpp"
// #include "Scene/Scene.hpp"

// #include "Sphere/Sphere.hpp"

// #include "Light/Light.hpp"
#include "utils/vec/vec.hpp"

int main()
{
    vec3i v1 = {1, 2, 3};
    vec3i v2 = {3, 2, 1};
    auto v3 = v1 - v2;

    std::cout << (v1 == v2) << std::endl;

    return 0;

    // // Initialization
    // Window window({512, 512});
    // Camera camera({0, 0, 0}, {1, 1}, 1.5);
    // window.clear({0, 0, 0});

    // // Scene creation
    // std::vector<std::unique_ptr<Sphere>> objects;
    // objects.emplace_back(std::make_unique<Sphere>(
    //     (vec3d) {0, 0, 2},
    //     1,
    //     (color_t) {0, 155, 0, 255}
    // ));

    // std::vector<std::unique_ptr<LightSource>> light_sources;
    // light_sources.emplace_back(std::make_unique<DirectionalLight>(
    //     1.0,
    //     (color_t) {255, 0, 255, 255},
    //     (vec3d) {1, -1, 1}
    // ));

    // Scene scene(objects, light_sources);

    // scene.render(window, camera);
    // std::cout << "Rendered!" << std::endl;

    // unsigned int this_frame_time = 0;
    // unsigned int delta_time = 0;
    // unsigned int prev_frame_time = 0;

    // while (window.is_running())
    // {
    //     this_frame_time = SDL_GetTicks();
    //     delta_time = this_frame_time - prev_frame_time;

    //     window.poll_events();

    //     // window.clear({0, 0, 0});
    //     // Render calls

    //     // std::cout << "Frametime: " << delta_time << std::endl;
    //     window.swap_buffers();

    //     prev_frame_time = this_frame_time;
    // }

    // return 0;
}
