#include "Triangle.hpp"
#include "utils/roughly_equal_to.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

Triangle::Triangle(Color color, double shininess, double reflectiveness,
                   vec3d A, vec3d B, vec3d C) :
                   Plane(color, shininess, reflectiveness, A, B, C)
{
    this->A = A;
    this->B = B;
    this->C = C;

    this->AB = this->B - this->A;
    this->BC = this->C - this->B;
    this->CA = this->A - this->C;
}

// Partially copy-pasted from `Plane` class
double Triangle::find_closest_intersection(vec3d& point, vec3d& direction)
{
    // copy-pasted
    double t = ( this->normal * (this->point - point) ) / ( this->normal * direction );
    if (t <= tolerance)  // only positive t
        return qNaN;

    return (this->is_point_in_triangle(this->A, this->B, this->C, point + direction * t)) ? t : qNaN;
}

// Assumes that point P lies in triangle's plane!
bool Triangle::is_point_in_triangle(vec3d A, vec3d B, vec3d C, vec3d P)
{
    vec3d AP = P - this->A;
    vec3d BP = P - this->B;
    vec3d CP = P - this->C;

    // Calculate barycentric coordinates
    double S1 = AP.cross_product(this->AB).magnitude() / 2;
    double S2 = BP.cross_product(this->BC).magnitude() / 2;
    double S3 = CP.cross_product(this->CA).magnitude() / 2;
    double S = (-this->CA).cross_product(this->AB).magnitude() / 2;
    double alpha = S1 / S;
    double beta  = S2 / S;
    double gamma = S3 / S;

    if ((0 <= alpha && alpha <= 1) && (0 <= beta && beta <= 1) && (0 <= gamma && gamma <= 1) && roughly_equal_to(alpha + beta + gamma, 1.0))
        return true;

    return false;
}
