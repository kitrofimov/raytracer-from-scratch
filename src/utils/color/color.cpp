#include <stdexcept>
#include <vector>
#include "Color.hpp"
#include "utils/vec/vec4.hpp"

Color::Color()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(std::vector<unsigned char> vector)
{
    this->r = vector[0];
    this->g = vector[1];
    this->b = vector[2];
    this->a = vector[3];
}

template <typename T>
Color::Color(vec4<T> vec)
{
    this->r = (unsigned char) vec.x;
    this->g = (unsigned char) vec.y;
    this->b = (unsigned char) vec.z;
    this->a = (unsigned char) vec.w;
}

Color Color::operator+(Color other) const
{
    Color result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int temp = (int) (*this)[i] + (int) other[i];
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

Color Color::operator-(Color other) const
{
    Color result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int temp = (int) (*this)[i] - (int) other[i];
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

Color Color::operator*(double scalar) const
{
    Color result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        double temp = (double) (*this)[i] * scalar;
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

Color Color::operator/(double scalar) const
{
    Color result = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        double temp = (double) (*this)[i] / scalar;
        result[i] = (temp < 0) ? 0 : ((temp > 255) ? 255 : temp);
    }
    return result;
}

Color& Color::operator+=(Color other)
{
    *this = *this + other;
    return *this;
}

unsigned char Color::operator[](int i) const
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
        throw std::out_of_range("color_t invalid index " + i);
        break;
    }
}

unsigned char& Color::operator[](int i)
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
        throw std::out_of_range("color_t invalid index " + i);
        break;
    }
}

template <typename T>
Color::operator vec4<T>() const
{
    return vec4<T>{
        (T) this->r,
        (T) this->g,
        (T) this->b,
        (T) this->a
    };
}

Color Color::mix(std::vector<Color> list)
{
    vec4i result = {0, 0, 0, 0};
    for (auto& color : list)
        result = result + (vec4i) color;
    result = result / list.size();
    return Color(result);
}
