#pragma once

#include <vector>
#include "Object/Object.hpp"
#include "Object/Polygon/Polygon.hpp"
#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

class Parallelepiped : public Object
{
public:
    Parallelepiped(Color color, double shininess, double reflectiveness,
                   vec3d vertex, vec3d edge1, vec3d edge2, vec3d edge3);

    double find_closest_intersection(vec3d& point, vec3d& direction) override;
    vec3d get_normal(vec3d& point) override;

private:
    std::vector<Polygon> faces;
};
