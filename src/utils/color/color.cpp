#include <stdexcept>
#include "color.hpp"

color_t color_t::operator+(color_t other)
{
    color_t result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int temp = (int) (*this)[i] + (int) other[i];
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

color_t color_t::operator-(color_t other)
{
    color_t result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int temp = (int) (*this)[i] - (int) other[i];
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

color_t color_t::operator*(double scalar)
{
    color_t result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        double temp = (double) (*this)[i] * scalar;
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

color_t color_t::operator/(double scalar)
{
    color_t result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        double temp = (double) (*this)[i] / scalar;
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

color_t color_t::operator+=(color_t other)
{
    *this = *this + other;
    return *this;
}

unsigned char color_t::operator[](int i) const
{
    switch (i)
    {
    case 0:
        return this->r;
        break;
    case 1:
        return this->g;
        break;
    case 2:
        return this->b;
        break;
    case 3:
        return this->a;
        break;
    default:
        throw std::out_of_range(std::string("color_t invalid index ") + std::to_string(i));
        break;
    }
}

unsigned char& color_t::operator[](int i)
{
    switch (i)
    {
    case 0:
        return this->r;
        break;
    case 1:
        return this->g;
        break;
    case 2:
        return this->b;
        break;
    case 3:
        return this->a;
        break;
    default:
        throw std::out_of_range(std::string("color_t invalid index ") + std::to_string(i));
        break;
    }
}
