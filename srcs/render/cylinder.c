#include "minirt.h"

#include <math.h>
#include <stdbool.h>

float vec3_length(t_vec v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

bool intersect_ray_plane(t_ray ray, t_vec planePoint, t_vec planeNormal, float *t) {
	float denom = dot_product(planeNormal, ray.dir);
	if (fabs(denom) > 0.) { // Ensure not parallel
		t_vec p0l0 = vec_substract(planePoint, ray.origin);
		*t = dot_product(p0l0, planeNormal) / denom;
		return *t >= 0;
	}
	return false;
}

t_vec vec_negate(t_vec v) {
	t_vec result;
	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return result;
}


void intersection_point_cylinder(t_inter *inter, t_objs *cylinder) {
	t_vec co = vec_substract(inter->ray.origin, cylinder->pos);
	float coDotDir = dot_product(co, cylinder->dir);
	t_vec a = vec_substract(inter->ray.dir, vec_multiply_float(cylinder->dir, dot_product(inter->ray.dir, cylinder->dir)));
	t_vec b = vec_substract(co, vec_multiply_float(cylinder->dir, coDotDir));
	float aDotA = dot_product(a, a);
	float bDotB = dot_product(b, b);
	float radiusSquared = cylinder->diameter / 2 * cylinder->diameter / 2;
	
	// Quadratic equation coefficients for cylinder side
	float A = aDotA;
	float B = 2 * dot_product(a, b);
	float C = bDotB - radiusSquared;
	
	// Discriminant
	float D = B * B - 4 * A * C;
	float tSide1 = FLT_MAX, tSide2 = FLT_MAX, tCap = FLT_MAX;
	bool hitSide = false, hitCap = false;

	if (D >= 0.) { // Potential side intersection
		float sqrtD = sqrtf(D);
		float t1 = (-B - sqrtD) / (2 * A);
		float t2 = (-B + sqrtD) / (2 * A);
		
		// Check if intersections are within cylinder caps
		float y1 = coDotDir + t1 * dot_product(inter->ray.dir, cylinder->dir);
		float y2 = coDotDir + t2 * dot_product(inter->ray.dir, cylinder->dir);
		if ((y1 >= 0. && y1 <= cylinder->height) && t1 > 0.) {
			tSide1 = t1;
			hitSide = true;
		}
		if ((y2 >= 0. && y2 <= cylinder->height) && t2 > 0. && t2 < tSide1) {
			tSide2 = t2;
			hitSide = true;
		}
	}

	// Check for cap intersections
	t_vec capTopCenter = vec_add(cylinder->pos, vec_multiply_float(cylinder->dir, cylinder->height));
	float tCapTop, tCapBottom;
	bool hitCapTop = intersect_ray_plane(inter->ray, capTopCenter, cylinder->dir, &tCapTop);
	bool hitCapBottom = intersect_ray_plane(inter->ray, cylinder->pos, cylinder->dir, &tCapBottom);
	
	// Check if intersection points are within the radius of the caps
	if (hitCapTop && vec3_length(vec_substract(vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, tCapTop)), capTopCenter)) <= cylinder->diameter / 2) {
		tCap = tCapTop;
		hitCap = true;
	}
	
	if (hitCapBottom && vec3_length(vec_substract(vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, tCapBottom)), cylinder->pos)) <= cylinder->diameter / 2) {
		if (tCapBottom < tCap) {
			tCap = tCapBottom;
			hitCap = true;
		}
	}

	// Find the closest intersection
	if (hitSide || hitCap) {
		float tMin = fmin(tSide1, fmin(tSide2, tCap));
		if (tMin > 0. && tMin < inter->dist) {
			inter->obj = cylinder;
			inter->dist = tMin;
			inter->point = vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, tMin));
			if (tMin == tSide1 || tMin == tSide2)
			{
				t_vec closestPointOnAxis = vec_add(cylinder->pos, vec_multiply_float(cylinder->dir, coDotDir + tMin * dot_product(inter->ray.dir, cylinder->dir)));
				inter->normal = vec_normalize(vec_substract(inter->point, closestPointOnAxis));
				// printf("cylinder->dir: %f %f %f\n", cylinder->dir.x, cylinder->dir.y, cylinder->dir.z);
				// printf("closestPointOnAxis: %f %f %f\n", closestPointOnAxis.x, closestPointOnAxis.y, closestPointOnAxis.z);
				// printf("inter->ray.dir: %f %f %f\n", inter->ray.dir.x, inter->ray.dir.y, inter->ray.dir.z);
				// printf("inter->normal: %f %f %f\n", inter->normal.x, inter->normal.y, inter->normal.z);
				// exit(1);
			}
			else if (tMin == tCapBottom)
				 inter->normal = vec_negate(cylinder->dir);
			else if (tMin == tCapTop)
				inter->normal = cylinder->dir;
		}
	}
}


