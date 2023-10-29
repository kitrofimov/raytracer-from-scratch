#pragma once

#include <vector>
#include "Object/Object.hpp"
#include "Object/Triangle/Triangle.hpp"
#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

// Uses clockwise orientation, assumes `points` lie on the same plane and ordered clockwise
// SHOULD BE A CONVEX POLYGON
class Polygon : public Object
{
public:
    Polygon(Color color, double shininess, double reflectiveness,
            std::vector<vec3d> points);

    double find_closest_intersection(vec3d& point, vec3d& direction) override;
    vec3d get_normal(vec3d& point) override;
    static std::vector<std::vector<vec3d>> triangulate(std::vector<vec3d> points);

private:
    std::vector<Triangle> triangles;
};
