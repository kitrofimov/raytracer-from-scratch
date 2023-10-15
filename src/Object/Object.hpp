#pragma once

#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

class Object
{
public:
    virtual ~Object() {};

    virtual double find_closest_intersection(vec3d& point, vec3d& direction) = 0;

    inline vec3d get_position() { return position; }
    inline Color get_color() { return color; }
    inline double get_shininess() { return shininess; }
    inline double get_reflectiveness() { return reflectiveness; }

protected:
    vec3d position;
    Color color;
    double shininess;
    double reflectiveness;
};
