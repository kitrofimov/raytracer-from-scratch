#include "Polygon.hpp"
#include "Object/Triangle/Triangle.hpp"
#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

Polygon::Polygon(Color color, double shininess, double reflectiveness,
                 std::vector<vec3d> points)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;

    std::vector<std::vector<vec3d>> triangulated = this->triangulate(points);
    for (auto& vertices : triangulated)
        this->triangles.emplace_back(color, shininess, reflectiveness, vertices[0], vertices[1], vertices[2]);
}

double Polygon::find_closest_intersection(vec3d& point, vec3d& direction)
{
    for (auto& triangle : this->triangles)
    {
        // Only one intersection is possible (in most cases)
        // So if we find one, we should not continue to look for another one
        double t = triangle.find_closest_intersection(point, direction);
        if (!std::isnan(t))
            return t;
    }
    return qNaN;
}

vec3d Polygon::get_normal(vec3d& point)
{
    return this->triangles[0].get_normal(point);
}

std::vector<std::vector<vec3d>> Polygon::triangulate(std::vector<vec3d> points)
{
    // wtf
    std::vector<std::vector<vec3d>> result;
    for (unsigned int i = 0; true; i += 2)
    {
        // OOB checks
        if (i >= points.size())
            return result;
        else if (i+1 >= points.size() || i+2 >= points.size())
        {
            result.push_back(std::vector<vec3d>({points[i], points[i+1], points[0]}));
            return result;
        }

        // if there is enough vertices yet
        result.push_back(std::vector<vec3d>({points[i], points[i+1], points[i+2]}));
    }
    return result;
}
