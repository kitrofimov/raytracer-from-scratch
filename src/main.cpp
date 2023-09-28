#define SDL_MAIN_HANDLED
#include <iostream>
#include <chrono>

#include "Window/Window.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "utils/vec/vec.hpp"
#include "constants.hpp"

int main()
{
    // Initialization
    Window window(vec2i(512, 512));
    window.clear(color_t(0, 0, 0, 255));
    Camera camera(vec3d(0, 0, 0), vec2d(1, 1), 1);
    Scene scene(scene_file_path);

    // Render the scene
    auto t1 = std::chrono::high_resolution_clock::now();
    scene.render(window, camera);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "Rendered in " << ms.count() <<  "ms" << std::endl;

    // Main loop
    while (window.is_running())
    {
        window.poll_events();
        window.swap_buffers();
    }

    return 0;
}
