#pragma once

#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

class Object
{
public:
    virtual ~Object() {};

    // Find a distance to closest intersection of a ray defined by point and direction with this object
    // Returns quiet NaN to show that there is no intersections at all or they are
    // happening in opposite direction from direction vector
    // Ignores t = 0 (does not count `point` itself as intersection if point lies on the object)
    virtual double find_closest_intersection(vec3d& point, vec3d& direction) = 0;

    // Get normal vector to a given point. Assumes that point lies on the object
    virtual vec3d get_normal(vec3d& point) = 0;

    inline Color get_color() { return color; }
    inline double get_shininess() { return shininess; }
    inline double get_reflectiveness() { return reflectiveness; }

protected:
    Color color;
    double shininess;
    double reflectiveness;
};
