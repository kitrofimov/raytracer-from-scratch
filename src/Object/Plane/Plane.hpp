#pragma once

#include "Object/Object.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"
#include "constants.hpp"

class Plane : public Object
{
public:
    Plane(Color color, double shininess, double reflectiveness,
          vec3d point, vec3d normal);
    Plane(Color color, double shininess, double reflectiveness,
          vec3d point1, vec3d point2, vec3d point3);

    double find_closest_intersection(vec3d& point, vec3d& direction) override;
    vec3d get_normal(vec3d& point) override;
    bool does_point_lie_on_plane(vec3d& point);

protected:
    vec3d normal;
    vec3d plane_point;
};
