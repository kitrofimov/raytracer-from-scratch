#include "color.hpp"

color_t color_t::operator*(double scalar)
{
    return {(unsigned char) ((double) this->r * scalar),
            (unsigned char) ((double) this->g * scalar),
            (unsigned char) ((double) this->b * scalar),
            (unsigned char) ((double) this->a * scalar)};
}

color_t color_t::operator/(double scalar)
{
    return {(unsigned char) ((double) this->r / scalar),
            (unsigned char) ((double) this->g / scalar),
            (unsigned char) ((double) this->b / scalar),
            (unsigned char) ((double) this->a / scalar)};
}

color_t color_t::operator+(color_t other)
{
    return {(unsigned char) (this->r + other.r),
            (unsigned char) (this->g + other.g),
            (unsigned char) (this->b + other.b),
            (unsigned char) (this->a + other.a)};
}

color_t color_t::operator+=(color_t other)
{
    *this = {(unsigned char) (this->r + other.r),
             (unsigned char) (this->g + other.g),
             (unsigned char) (this->b + other.b),
             (unsigned char) (this->a + other.a)};
    return *this;
}

color_t color_t::operator-(color_t other)
{
    return {(unsigned char) (this->r - other.r),
            (unsigned char) (this->g - other.g),
            (unsigned char) (this->b - other.b),
            (unsigned char) (this->a - other.a)};
}
