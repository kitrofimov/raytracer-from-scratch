#include <iostream>
#include <stdexcept>
#include "TerminalRenderer.hpp"
#include "ansi_codes.hpp"
#include "utils/vec/vec2.hpp"
#include "utils/in_range.hpp"

TerminalRenderer::TerminalRenderer(vec2i dimensions) :
    buffer(dimensions.y, std::vector<std::string>(dimensions.x, std::string()))
{
    this->dimensions = dimensions;
}

void TerminalRenderer::poll_events()
{

}

void TerminalRenderer::swap_buffers()
{
    std::cout << ERASE_IN_DISPLAY(2) << CURSOR_POSITION(0, 0);
    std::cout << this->concatenate_buffer();
}

void TerminalRenderer::draw_pixel(vec2i pos, Color c)
{
    this->buffer[pos.y][pos.x] = this->rgb_to_ansi(c);
}

std::string TerminalRenderer::concatenate_buffer()
{
    std::string res;
    for (int y = 0; y < this->dimensions.y; y++)
    {
        for (int x = 0; x < this->dimensions.x; x++)
            res += this->buffer[y][x];
        res += "\n";
    }
    return res;
}

std::string TerminalRenderer::rgb_to_ansi(Color c)
{
    // std::string chars = ".:-=+*#%@";
    std::string chars = ":-=+*#%@";
    double shade = (c.r + c.g + c.b) / 3;

    // 8 buckets
    for (int i = 0; i < 8; i++)
    {
        if (in_range(shade, 32*i, 32*(i+1)-1))
            return FOREGROUND_RGB(c.r, c.g, c.b) + chars.substr(i, 1) + RESET;
    }

    throw std::runtime_error("shade is not in specified 8 buckets!");
    return "";
}
