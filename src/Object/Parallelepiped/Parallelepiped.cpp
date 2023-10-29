#include <vector>
#include <limits>
#include <stdexcept>

#include "Parallelepiped.hpp"
#include "Object/Object.hpp"
#include "Object/Polygon/Polygon.hpp"
#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

Parallelepiped::Parallelepiped(Color color, double shininess, double reflectiveness,
                               vec3d vertex, vec3d edge1, vec3d edge2, vec3d edge3)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;

    std::vector<vec3d> v = {
        vertex, vertex+edge1, vertex+edge1+edge2, vertex+edge2,
        vertex+edge3, vertex+edge1+edge3, vertex+edge1+edge2+edge3, vertex+edge2+edge3
    };

    this->faces.push_back(Polygon(color, shininess, reflectiveness, {v[0], v[1], v[2], v[3]}));
    this->faces.push_back(Polygon(color, shininess, reflectiveness, {v[4], v[5], v[6], v[7]}));

    this->faces.push_back(Polygon(color, shininess, reflectiveness, {v[0], v[1], v[5], v[4]}));
    this->faces.push_back(Polygon(color, shininess, reflectiveness, {v[3], v[2], v[6], v[7]}));

    this->faces.push_back(Polygon(color, shininess, reflectiveness, {v[0], v[3], v[7], v[4]}));
    this->faces.push_back(Polygon(color, shininess, reflectiveness, {v[1], v[2], v[6], v[5]}));
}

double Parallelepiped::find_closest_intersection(vec3d& point, vec3d& direction)
{
    double min_t = std::numeric_limits<double>::max();
    for (auto& face : this->faces)
    {
        double t = face.find_closest_intersection(point, direction);
        if (t < min_t && !std::isnan(t))
            min_t = t;
    }
    if (min_t == std::numeric_limits<double>::max())
        return qNaN;
    return min_t;
}

vec3d Parallelepiped::get_normal(vec3d& point)
{
    for (auto& face : this->faces)
    {
        if (face.does_point_lie_on_plane(point))
            return face.get_normal(point);
    }
    throw std::invalid_argument("Provided point does not lie on this parallelepiped");
}
