#pragma once

#include "Object/Object.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"
#include "constants.hpp"

class Sphere : public Object
{
public:
    Sphere(vec3d position,
           double radius,
           Color color,
           double shininess = qNaN,
           double reflectiveness = 0);

    // Find a distance to closest intersection of a ray defined by point and direction with this sphere
    // Returns quiet NaN to show that there is no intersections at all or they are
    // happening in opposite direction from direction vector
    // Ignores t = 0 (does not count `point` itself as intersection if point lies on the sphere)
    double find_closest_intersection(vec3d& point, vec3d& direction) override;

    inline double get_radius() { return radius; }

private:
    double radius;
};
