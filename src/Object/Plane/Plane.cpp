#include "Plane.hpp"
#include "utils/color/color.hpp"
#include "utils/vec/vec3.hpp"

#include "utils/roughly_equal_to.hpp"

// Let normal vector N = {A; B; C} and M and K - points on the plane
// MK - vector from M to K, MK = {xk - xm, yk - ym, zk - zm}
// MK*N = 0 (cos 90deg = 0)
// MKx * Nx + MKy * Ny + MKz * Nz = 0
// A(xk - xm) + B(yk - ym) + C(zk - zm) = 0
// A*xk + B*yk + C*zk - A*xm - B*ym - C*zm = 0
// D = - A*xm - B*ym - C*zm
// A*xk + B*yk + C*zk + D = 0
// Let K be *arbitrary* point on the plane
// Then A*x + B*y + C*z + D = 0 (GENERAL EQUATION OF THE PLANE)

Plane::Plane(Color color, double shininess, double reflectiveness,
             vec3d point, vec3d normal)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;
    this->plane_point = point;
    this->normal = normal.normalize();
}

Plane::Plane(Color color, double shininess, double reflectiveness,
             vec3d point1, vec3d point2, vec3d point3)
{
    this->color = color;
    this->shininess = shininess;
    this->reflectiveness = reflectiveness;
    this->plane_point = point1;
    vec3d v1 = point2 - point1;
    vec3d v2 = point3 - point1;
    this->normal = v1.cross_product(v2).normalize();
}

// `Polygon::find_closest_intersection` SHOULD BE CHANGED TOO IF THIS IS CHANGED!
double Plane::find_closest_intersection(vec3d& point, vec3d& direction)
{
    // Let there be a ray P + tD and plane N*A = N*B (N - normal, A and B - points on the plane)
    // Assume there is an intersection in point C
    // Then C = P + tD and N*C = N*A = N*B
    // N*(P + tD) = N*A
    // N*P + N*D*t = N*A
    // N*D*t = N*A - N*P
    // t = ( N(A - P) ) / ( N*D )

    double t = ( this->normal * (this->plane_point - point) ) / ( this->normal * direction );
    return (t > tolerance) ? t : qNaN;
}

vec3d Plane::get_normal(vec3d& point)
{
    return this->normal;
}

// Checks the validity of general equation of this plane
// (see the comment on the top of Plane.cpp)
bool Plane::does_point_lie_on_plane(vec3d& point)
{
    double D = -(this->normal.x * this->plane_point.x) - \
                (this->normal.y * this->plane_point.y) - \
                (this->normal.z * this->plane_point.z);

    double check_value = (this->normal.x * point.x) + \
                         (this->normal.y * point.y) + \
                         (this->normal.z * point.z) +\
                         D;

    if (roughly_equal_to(check_value, 0.0))
        return true;
    return false;
}
