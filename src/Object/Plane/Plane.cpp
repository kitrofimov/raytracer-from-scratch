#include "Plane.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

Plane::Plane(Color color, double shininess, double reflectiveness,
             vec3d point, vec3d normal)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;
    this->point = point;
    this->normal = normal.normalize();
}

Plane::Plane(Color color, double shininess, double reflectiveness,
             vec3d point1, vec3d point2, vec3d point3)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;
    this->point = point1;
    vec3d v1 = point2 - point1;
    vec3d v2 = point3 - point1;
    this->normal = v1.cross_product(v2).normalize();
}

// `Triangle::find_closest_intersection` SHOULD BE CHANGED TOO IF THIS IS CHANGED!
// `point` - start of a ray
double Plane::find_closest_intersection(vec3d& point, vec3d& direction)
{
    // Let there be a ray P + tD and plane N*A = N*B (N - normal, A and B - points on the plane)
    // Assume there is an intersection in point C
    // Then C = P + tD and N*C = N*A = N*B
    // N*(P + tD) = N*A
    // N*P + N*D*t = N*A
    // N*D*t = N*A - N*P
    // t = ( N(A - P) ) / ( N*D )

    double t = ( this->normal * (this->point - point) ) / ( this->normal * direction );
    return (t > tolerance) ? t : qNaN;
}

vec3d Plane::get_normal(vec3d& point)
{
    return this->normal;
}
