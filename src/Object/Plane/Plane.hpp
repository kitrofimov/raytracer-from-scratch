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

    double find_closest_intersection(vec3d& point, vec3d& direction) override;
    vec3d get_normal(vec3d& point) override;

private:
    vec3d normal;
    vec3d point;
};
