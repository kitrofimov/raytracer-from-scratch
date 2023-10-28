#define SDL_MAIN_HANDLED
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "Renderer/SDLRenderer/SDLRenderer.hpp"
#include "Renderer/TerminalRenderer/TerminalRenderer.hpp"
#include "Camera/Camera.hpp"
#include "Scene/Scene.hpp"
#include "utils/vec/vec.hpp"
#include "utils/get_terminal_size/get_terminal_size.hpp"
#include "utils/Argparser/Argparser.hpp"
#include "constants.hpp"

int main(int argc, char** argv)
{
    // Argument parsing
    std::vector<std::string> boolean_args = {
        "--terminal-rendering",
        "--save"
    };
    std::unordered_map<std::string, std::string> string_args = {
        {"--save-filename", "render"}
    };
    Argparser argparser(argc, argv, boolean_args, string_args);

    if (argparser.help)
    {
        std::cout <<
            "RAYTRACER made by fahlerile\n"
            "https://github.com/fahlerile/raytracer-from-scratch\n\n"
            "Available CLI options:\n"
            "--terminal-rendering - render in terminal using colored ASCII\n"
            "--save - save rendered image to .BMP, or to .ANS if --terminal-rendering (open .ANS with cat tool)\n"
            "--save-filename={FILENAME} - file to save rendered image to (works only if --save is enabled)\n"
            "--help - show this message"
        << std::endl;
        return 0;
    }

    // Initialization
    Camera camera(vec3d(0, 0, 0), vec2d(1, 1), 1);
    Scene scene(scene_file_path);
    std::unique_ptr<Renderer> renderer;

    if (argparser.parsed_boolean["--terminal-rendering"])
        renderer = std::make_unique<TerminalRenderer>(get_terminal_size());
    else
        renderer = std::make_unique<SDLRenderer>(vec2i(512, 512));

    // Render the scene
    auto t1 = std::chrono::high_resolution_clock::now();
    scene.render(renderer, camera);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "Rendered in " << ms.count() << "ms" << std::endl;

    renderer->swap_buffers();
    if (argparser.parsed_boolean["--save"])
        renderer->save_buffer(argparser.parsed_string["--save-filename"]);

    if (!argparser.parsed_boolean["--terminal-rendering"])
    {
        while (renderer->is_running())
        {
            renderer->poll_events();
            renderer->swap_buffers();
        }
    }

    return 0;
}
