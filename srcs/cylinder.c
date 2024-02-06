#include "minirt.h"

#include <math.h>
#include <stdbool.h>

t_vec vec3_sub(t_vec a, t_vec b) {
    t_vec result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

t_vec vec3_scale(t_vec v, float s) {
    t_vec result = {v.x * s, v.y * s, v.z * s};
    return result;
}

float vec3_dot(t_vec a, t_vec b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec vec3_cross(t_vec a, t_vec b) {
    t_vec result = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return result;
}

//VERSION 1

/* void intersection_point_cylinder(t_inter *inter, t_objs *cylinder) {
    t_vec co = vec3_sub(inter->ray.origin, cylinder->pos);
    float coDotDir = vec3_dot(co, cylinder->dir);
    t_vec a = vec3_sub(inter->ray.dir, vec3_scale(cylinder->dir, vec3_dot(inter->ray.dir, cylinder->dir)));
    t_vec b = vec3_sub(co, vec3_scale(cylinder->dir, coDotDir));
    float aDotA = vec3_dot(a, a);
    float bDotB = vec3_dot(b, b);
    float radiusSquared = cylinder->diameter / 2 * cylinder->diameter / 2;
    
    // Quadratic equation coefficients
    float A = aDotA;
    float B = 2 * vec3_dot(a, b);
    float C = bDotB - radiusSquared;
    
    // Discriminant
    float D = B * B - 4 * A * C;
    if (D < 0) return ; // No intersection
    
    float sqrtD = sqrtf(D);
    float t1 = (-B - sqrtD) / (2 * A);
    float t2 = (-B + sqrtD) / (2 * A);
    
    // Check if intersections are within cylinder caps
    float y1 = coDotDir + t1 * vec3_dot(inter->ray.dir, cylinder->dir);
    float y2 = coDotDir + t2 * vec3_dot(inter->ray.dir, cylinder->dir);
    bool withinCaps1 = y1 >= 0 && y1 <= cylinder->height;
    bool withinCaps2 = y2 >= 0 && y2 <= cylinder->height;

    if (withinCaps1 && t1 > 0) {
        inter->obj = cylinder;
		inter->dist = t1;
		inter->point = vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, t1));
        inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
    } else if (withinCaps2 && t2 > 0) {
        inter->obj = cylinder;
		inter->dist = t2;
		inter->point = vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, t2));
        inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
    }

    return ; // Intersection occurs outside the cylinder caps
} */




//VERSION 2 avec plans au bout

float vec3_length(t_vec v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

bool intersect_ray_plane(t_ray ray, t_vec planePoint, t_vec planeNormal, float *t) {
    float denom = vec3_dot(planeNormal, ray.dir);
    if (fabs(denom) > 1e-6) { // Ensure not parallel
        t_vec p0l0 = vec3_sub(planePoint, ray.origin);
        *t = vec3_dot(p0l0, planeNormal) / denom;
        return *t >= 0;
    }
    return false;
}

void intersection_point_cylinder(t_inter *inter, t_objs *cylinder) {
    t_vec co = vec3_sub(inter->ray.origin, cylinder->pos);
    float coDotDir = vec3_dot(co, cylinder->dir);
    t_vec a = vec3_sub(inter->ray.dir, vec3_scale(cylinder->dir, vec3_dot(inter->ray.dir, cylinder->dir)));
    t_vec b = vec3_sub(co, vec3_scale(cylinder->dir, coDotDir));
    float aDotA = vec3_dot(a, a);
    float bDotB = vec3_dot(b, b);
    float radiusSquared = cylinder->diameter / 2 * cylinder->diameter / 2;
    
    // Quadratic equation coefficients for cylinder side
    float A = aDotA;
    float B = 2 * vec3_dot(a, b);
    float C = bDotB - radiusSquared;
    
    // Discriminant
    float D = B * B - 4 * A * C;
    float tSide1 = FLT_MAX, tSide2 = FLT_MAX, tCap = FLT_MAX;
    bool hitSide = false, hitCap = false;

    if (D >= 0) { // Potential side intersection
        float sqrtD = sqrtf(D);
        float t1 = (-B - sqrtD) / (2 * A);
        float t2 = (-B + sqrtD) / (2 * A);
        
        // Check if intersections are within cylinder caps
        float y1 = coDotDir + t1 * vec3_dot(inter->ray.dir, cylinder->dir);
        float y2 = coDotDir + t2 * vec3_dot(inter->ray.dir, cylinder->dir);
        if ((y1 >= 0 && y1 <= cylinder->height) && t1 > 0) {
            tSide1 = t1;
            hitSide = true;
        }
        if ((y2 >= 0 && y2 <= cylinder->height) && t2 > 0 && t2 < tSide1) {
            tSide2 = t2;
            hitSide = true;
        }
    }

    // Check for cap intersections
    t_vec capTopCenter = vec_add(cylinder->pos, vec3_scale(cylinder->dir, cylinder->height));
    float tCapTop, tCapBottom;
    bool hitCapTop = intersect_ray_plane(inter->ray, capTopCenter, cylinder->dir, &tCapTop);
    bool hitCapBottom = intersect_ray_plane(inter->ray, cylinder->pos, cylinder->dir, &tCapBottom);
    
    // Check if intersection points are within the radius of the caps
    if (hitCapTop && vec3_length(vec3_sub(vec_add(inter->ray.origin, vec3_scale(inter->ray.dir, tCapTop)), capTopCenter)) <= cylinder->diameter / 2) {
        tCap = tCapTop;
        hitCap = true;
    }
    
    if (hitCapBottom && vec3_length(vec3_sub(vec_add(inter->ray.origin, vec3_scale(inter->ray.dir, tCapBottom)), cylinder->pos)) <= cylinder->diameter / 2) {
        if (tCapBottom < tCap) {
            tCap = tCapBottom;
            hitCap = true;
        }
    }

    // Find the closest intersection
    if (hitSide || hitCap) {
        float tMin = fmin(tSide1, fmin(tSide2, tCap));
        if (tMin < FLT_MAX) {
            inter->obj = cylinder;
            inter->dist = tMin;
            inter->point = vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, tMin));
            inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
        }
    }
}


