#pragma once

inline vec3d reflect_ray(vec3d ray, vec3d normal)
{
    return 2 * normal * (ray * normal) - ray;
}
