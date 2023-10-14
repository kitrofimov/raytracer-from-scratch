#pragma once
#include <string>
#include <utility>
#include "Renderer/Renderer.hpp"

class TerminalRenderer : public Renderer
{
public:
    TerminalRenderer(vec2i dimensions);

    void poll_events() override;
    void swap_buffers() override;
    void draw_pixel(vec2i pos, Color c) override;
    void save_buffer(std::string filename) override;

private:
    std::vector<std::vector<std::string>> buffer;

    std::string concatenate_buffer();
    std::string rgb_to_ansi(Color c);
};
