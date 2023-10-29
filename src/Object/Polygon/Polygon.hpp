#pragma once

#include <vector>
#include "Object/Plane/Plane.hpp"
#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"

// Uses clockwise orientation, assumes `vertices` lie on the same plane
// SHOULD BE A CONVEX POLYGON!
class Polygon : public Plane
{
public:
    Polygon(Color color, double shininess, double reflectiveness,
            std::vector<vec3d> vertices);

    double find_closest_intersection(vec3d& point, vec3d& direction) override;
    bool is_point_in_polygon(vec3d point);

private:
    // Calculates polygon's area by triangulation
    // Should be called after edge_vectors computataion
    double calculate_area();

    std::size_t n_edges;
    double area;
    std::vector<vec3d> vertices;
    std::vector<vec3d> edge_vectors;  // v0v1, v1v2, v2v3, ..., vn-1vn, vnv0
};
