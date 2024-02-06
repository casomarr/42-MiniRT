/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:09:52 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/06 00:42:22 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Function that creates an orthonormal basis given a single vector w.
To do so, it creates two arbitrary vectors not parallel to w */
/* void create_basis(t_vec cylinder_dir, t_vec *up, t_vec *right) 
{
	t_vec a;

	if (fabs(cylinder_dir.x) < 0.9)
		a = create_vec(1, 0, 0);
	else
		a = create_vec(0, 1, 0);
	*right = vec_normalize(vec_cross(cylinder_dir, a));
	*up = vec_normalize(vec_cross(cylinder_dir, *right));
} */

void create_basis(t_vec cylinder_dir, t_vec *up, t_vec *right) {
    t_vec w = vec_normalize(cylinder_dir); // Normalize cylinder direction

    // Choose a vector that is most orthogonal to w to minimize numerical errors
    t_vec tentative_up = fabs(w.y) > fabs(w.x) ? create_vec(1, 0, 0) : create_vec(0, 1, 0);

    // Generate an orthogonal vector to both w and the tentative up vector, which will be our right vector
    *right = vec_normalize(vec_cross(w, tentative_up));

    // Generate the true up vector, orthogonal to both w and right
    *up = vec_cross(*right, w); // Already normalized by the cross product properties

    // Note: No need to normalize *up as the cross product of two normalized, perpendicular vectors is also normalized
}

/* Transforms the ray values into the cylinder's local space (internal
model of coordonates vs real world coordonates) */
/* t_ray transform_ray_to_local(t_ray world_ray, t_objs *cylinder) {
    t_ray local_ray;
    t_vec up;
    t_vec right;

    create_basis(cylinder->dir, &up, &right);
    local_ray.origin = vec_substract(world_ray.origin, cylinder->pos);

    local_ray.origin.x = dot_product(local_ray.origin, right);
    local_ray.origin.y = dot_product(local_ray.origin, up);
    local_ray.origin.z = dot_product(local_ray.origin, cylinder->dir);

    local_ray.dir = world_ray.dir;

    local_ray.dir.x = dot_product(world_ray.dir, right);
    local_ray.dir.y = dot_product(world_ray.dir, up);
    local_ray.dir.z = dot_product(world_ray.dir, cylinder->dir);

    local_ray.dir = vec_normalize(local_ray.dir);
    return local_ray;
} */

t_ray transform_ray_to_local(t_ray world_ray, t_objs *cylinder) {
    t_ray local_ray;
    t_vec up;
    t_vec right;
    t_vec local_origin;
    t_vec local_dir;

    create_basis(cylinder->dir, &up, &right);
    local_origin = vec_substract(world_ray.origin, cylinder->pos);

    local_ray.origin.x = dot_product(local_origin, right);
    local_ray.origin.y = dot_product(local_origin, up);
    local_ray.origin.z = dot_product(local_origin, cylinder->dir);

    local_dir.x = dot_product(world_ray.dir, right);
    local_dir.y = dot_product(world_ray.dir, up);
    local_dir.z = dot_product(world_ray.dir, cylinder->dir);

    local_ray.dir = vec_normalize(local_dir);

    return local_ray;
}

/* Checks if camera_ray intersects with the upper plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
static float	upper_plane(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	boundaries;
	t_ray local_ray;

	local_ray = transform_ray_to_local(inter->ray, cylinder);
	t = (cylinder->pos.z + cylinder->height/*  / 2 */ - local_ray.origin.z) / local_ray.dir.z;
	boundaries = sqrtf((local_ray.origin.x + t * local_ray.dir.x - cylinder->pos.x) * \
	(local_ray.origin.x + t * local_ray.dir.x - cylinder->pos.x) + \
	(local_ray.origin.y + t * local_ray.dir.y - cylinder->pos.y) * \
	(local_ray.origin.y + t * local_ray.dir.y - cylinder->pos.y));
	if (t > 0 && boundaries <= cylinder->diameter / 2)
		return (t);
	// printf("local_ray.origin = %f %f %f\n", local_ray.origin.x, local_ray.origin.y, local_ray.origin.z);
	return (0);
}

/* Checks if camera_ray intersects with the bottom plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
static float	bottom_plane(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	boundaries;
	t_ray local_ray;

	local_ray = transform_ray_to_local(inter->ray, cylinder);
	t = (cylinder->pos.z - cylinder->height/*  / 2 */ - local_ray.origin.z) / local_ray.dir.z;
	boundaries = sqrtf((local_ray.origin.x + t * local_ray.dir.x - cylinder->pos.x) * \
	(local_ray.origin.x + t * local_ray.dir.x - cylinder->pos.x) + \
	(local_ray.origin.y + t * local_ray.dir.y - cylinder->pos.y) * \
	(local_ray.origin.y + t * local_ray.dir.y - cylinder->pos.y));
	if (t > 0 && boundaries <= cylinder->diameter / 2)
		return (t);
	return (0);
}

/* Calculates the variables a, b and c (maths.x, maths.y and maths.z)
to calculate delta further on */
static t_vec	get_vec_abc(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	t_ray	ray;
	t_ray local_ray;

	local_ray = transform_ray_to_local(inter->ray, cylinder);
	ray = local_ray;
	maths.x = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	maths.y = 2 * (ray.dir.x * (ray.origin.x - cylinder->pos.x) + 
		ray.dir.y * (ray.origin.y - cylinder->pos.y));
	maths.z = (ray.origin.x - cylinder->pos.x) * (ray.origin.x - cylinder->pos.x) + 
		(ray.origin.y - cylinder->pos.y) * (ray.origin.y - cylinder->pos.y) - 
		(cylinder->diameter / 2) * (cylinder->diameter / 2);
	return(maths);
}

/* Returns the closest intersection distance if multiple */
static float	smaller_t(t_vec maths, float delta, t_objs *cylinder, t_inter *inter)
{
	float	t;
	float	t1;
	float	t2;
	float	z1;
	float	z2;
	t_ray local_ray;

	t = FLT_MAX;
	t1 = (-maths.y + sqrt(delta)) / (2 * maths.x);
	t2 = (-maths.y - sqrt(delta)) / (2 * maths.x);
	local_ray = transform_ray_to_local(inter->ray, cylinder);
	z1 = local_ray.origin.z + t1 * local_ray.dir.z;
	z2 = local_ray.origin.z + t2 * local_ray.dir.z;
	if (z1 >= cylinder->pos.z - cylinder->height && z1 <= cylinder->pos.z + cylinder->height)
	{
		if (t1 > 0)
			t = t1;
	}
	if (z2 >= cylinder->pos.z - cylinder->height && z2 <= cylinder->pos.z + cylinder->height)
	{
		if (t2 > 0 && t2 < t)
			t = t2;
	}
	return (t);
}

/* Checks if the ray intersects with the tube (if delta > 0)
and if the intersection happens inside the cylinder's height */
static float	tube(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	float	delta;
	float	t;

	t = FLT_MAX;
	maths = get_vec_abc(inter, cylinder);
	delta = maths.y * maths.y - 4 * maths.x * maths.z;
	if (delta >= 0)
		t = smaller_t(maths, delta, cylinder, inter);
	if (t != FLT_MAX)
		return (t);
	else
		return (0);
}

/* Returns the closest intersection point. If there was no intersection
between the ray and one of the objects (the tube or the two planes), their
associated t will have a value of FLT_MAX */
static float	closest_t(float t_top, float t_bottom, float t_side)
{
	float	t;
	
	t = FLT_MAX;
	if (t_top > 0 && t_top < t)
		t = t_top;
	if (t_bottom > 0 && t_bottom < t)
		t = t_bottom;
	if (t_side > 0 && t_side < t)
		t = t_side;
	if (t != FLT_MAX)
		return (t);
	else
		return (0);
}

t_vec vec_transform_to_world(t_vec local_vec, t_vec up, t_vec right, t_vec cylinder_dir)
{
	return vec_add(vec_add(vec_multiply_float(right, local_vec.x), \
	vec_multiply_float(up, local_vec.y)), vec_multiply_float(cylinder_dir, local_vec.z));
}

void	transform_back_to_world_coordinates(t_inter *inter, t_objs *cylinder)
{
	t_vec up;
	t_vec right;

	create_basis(cylinder->dir, &up, &right);
	inter->point = vec_add(cylinder->pos, vec_transform_to_world(inter->point, up, right, cylinder->dir));
	inter->normal = vec_transform_to_world(inter->normal, up, right, cylinder->dir);
}

/* Divides the cylinder into three objects : two planes and a tube.
Then checks if the camera_ray intersects with any of these three objects */
void intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	t_top;
	float	t_bottom;
	float	t_side;
	
	t = 0.;
	t_top = upper_plane(inter, cylinder);
	t_bottom = bottom_plane(inter, cylinder);
	t_side = tube(inter, cylinder);

	t = closest_t(t_top, t_bottom, t_side);
	if (t > 0)
	{
		inter->obj = cylinder;
		inter->dist = t;
		inter->point = vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, t));
		if (t == t_side)
			inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
		else if (t == t_top)
			inter->normal = create_vec(0, 1, 0);
		else if (t == t_bottom)
			inter->normal = create_vec(0, -1, 0);
		transform_back_to_world_coordinates(inter, cylinder);
	}
}
