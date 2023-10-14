#define SDL_MAIN_HANDLED
#include <iostream>
#include <chrono>

#include "Renderer/SDLRenderer/SDLRenderer.hpp"
#include "Renderer/TerminalRenderer/TerminalRenderer.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "utils/vec/vec.hpp"
#include "utils/get_terminal_size/get_terminal_size.hpp"
#include "constants.hpp"

void print_help();

int main(int argc, char** argv)
{
    bool terminal_rendering;
    vec2i terminal_dimensions;
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg == "--help")
            print_help();
        else if (arg == "--terminal-rendering")
        {
            terminal_rendering = true;
            terminal_dimensions = get_terminal_size();
        }
        else
            print_help();
    }

    // Initialization
    Camera camera(vec3d(0, 0, 0), vec2d(1, 1), 1);
    Scene scene(scene_file_path);
    std::unique_ptr<Renderer> renderer;

    if (!terminal_rendering)
        renderer = std::make_unique<Window>(vec2i(512, 512));
    else
        renderer = std::make_unique<TerminalRenderer>(terminal_dimensions);

    // Render the scene
    auto t1 = std::chrono::high_resolution_clock::now();
    scene.render(renderer, camera);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "Rendered in " << ms.count() << "ms" << std::endl;

    renderer->swap_buffers();

    if (!terminal_rendering)
    {
        while (renderer->is_running())
        {
            renderer->poll_events();
            renderer->swap_buffers();
        }
    }

    return 0;
}

void print_help()
{
    std::cout << "RAYTRACER made by fahlerile\n"
                 "https://github.com/fahlerile/raytracer-from-scratch\n\n"
                 "Available CLI options:\n"
                 "--terminal-rendering - render in terminal using colored ASCII\n"
                 "--help - show this message" << std::endl;
    std::exit(0);
}
