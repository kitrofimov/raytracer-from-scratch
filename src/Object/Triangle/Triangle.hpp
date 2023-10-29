#pragma once

#include "Object/Plane/Plane.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

// Uses clockwise orientation
class Triangle : public Plane
{
public:
    Triangle(Color color, double shininess, double reflectiveness,
             vec3d A, vec3d B, vec3d C);

    double find_closest_intersection(vec3d& point, vec3d& direction) override;
    bool is_point_in_triangle(vec3d A, vec3d B, vec3d C, vec3d P);

private:
    vec3d A, B, C;
    vec3d AB, BC, CA;
};
