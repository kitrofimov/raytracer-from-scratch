#pragma once

// Reflect a ray against a normal (alpha = beta)
inline vec3d reflect_ray(vec3d ray, vec3d normal)
{
    return 2 * normal * (ray * normal) - ray;
}
