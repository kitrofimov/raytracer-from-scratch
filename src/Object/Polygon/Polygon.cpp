#include <algorithm>
#include <numeric>

#include "Polygon.hpp"
#include "utils/Color/Color.hpp"
#include "utils/vec/vec3.hpp"
#include "utils/roughly_equal_to.hpp"

Polygon::Polygon(Color color, double shininess, double reflectiveness,
                 std::vector<vec3d> vertices) :
                 Plane(color, shininess, reflectiveness, vertices[0], vertices[1], vertices[2]),
                 edge_vectors(vertices.size(), vec3d())
{
    this->vertices = vertices;
    this->n_edges = vertices.size();

    if (this->n_edges < 3)
        throw std::invalid_argument("Polygon should have at least 3 vertices!");

    for (std::size_t i = 0; i < this->n_edges; i++)
    {
        if (i == this->n_edges - 1)
            this->edge_vectors[i] = this->vertices[0] - this->vertices[i];
        else
            this->edge_vectors[i] = this->vertices[i+1] - this->vertices[i];
    }

    this->area = this->calculate_area();
}

// Partially copy-pasted from `Plane` class
double Polygon::find_closest_intersection(vec3d& point, vec3d& direction)
{
    double t = ( this->normal * (this->plane_point - point) ) / ( this->normal * direction );
    if (t <= tolerance)  // only positive t
        return qNaN;

    return (this->is_point_in_polygon(point + direction * t)) ? t : qNaN;
}

bool Polygon::is_point_in_polygon(vec3d point)
{
    std::vector<vec3d> v2p_vectors(this->n_edges, vec3d());  // vertices to point vectors. v0p, v1p, v2p, ...
    for (std::size_t i = 0; i < this->n_edges; i++)
        v2p_vectors[i] = point - this->vertices[i];

    std::vector<double> barycentric(this->n_edges, 0);
    for (std::size_t i = 0; i < this->n_edges; i++)
    {
        double area_of_this_triangle = v2p_vectors[i].cross_product(this->edge_vectors[i]).magnitude() / 2;
        barycentric[i] = area_of_this_triangle / this->area;
    }

    // if all barycentric coordinates lie in range [0, 1] and sum of them is equal to 1
    bool greater_than_or_equal_to_zero = std::all_of(barycentric.cbegin(), barycentric.cend(), [](int i) { return 0 <= i; });
    bool less_than_or_equal_to_one = std::all_of(barycentric.cbegin(), barycentric.cend(), [](int i) { return i <= 1; });
    double sum = std::reduce(barycentric.begin(), barycentric.end());

    if (greater_than_or_equal_to_zero && less_than_or_equal_to_one && roughly_equal_to(sum, 1.0))
        return true;
    return false;
}

double Polygon::calculate_area()
{
    double area = 0;

    if (this->n_edges == 3)
        area = this->edge_vectors[2].cross_product(this->edge_vectors[0]).magnitude() / 2;

    for (std::size_t i = 2; i < this->n_edges; i++)
    {
        double area_of_this_triangle = (this->vertices[i] - this->vertices[0]).cross_product(-this->edge_vectors[i-1]).magnitude() / 2;
        area += area_of_this_triangle;
    }
    return area;
}
