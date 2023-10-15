#include "Sphere.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"
#include "utils/quadratic.hpp"

Sphere::Sphere(Color color, double shininess, double reflectiveness, vec3d position, double radius)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;
    this->position = position;
    this->radius = radius;
}

double Sphere::find_closest_intersection(vec3d& point, vec3d& direction)
{
    // CP = c2p, center to point vector, D = direction
    // (CP + tD)^2 = r^2
    // Solves for smallest positive t
    vec3d c2p = point - this->position;
    double a = direction * direction;
    double b = 2 * (c2p * direction);
    double c = (c2p * c2p) - std::pow(this->radius, 2);
    return solve_quadratic_for_smallest_positive(a, b, c);
}

vec3d Sphere::get_normal(vec3d& point)
{
    return (point - this->position).normalize();
}
