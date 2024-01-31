/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:09:52 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/31 17:02:30 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Checks if camera_ray intersects with the upper plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
static float	upper_plane(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	boundaries;

	t = (cylinder->pos.z + cylinder->height / 2 - inter->cam_ray.origin.z) / inter->cam_ray.dir.z;
	boundaries = sqrtf((inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) * \
	(inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) + \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y) * \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y));
	if (t > 0 && boundaries <= cylinder->diameter / 2)
		return (t);
	return (0);
}

/* Checks if camera_ray intersects with the bottom plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
static float	bottom_plane(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	boundaries;

	t = (cylinder->pos.z - cylinder->height / 2 - inter->cam_ray.origin.z) / inter->cam_ray.dir.z;
	boundaries = sqrtf((inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) * \
	(inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) + \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y) * \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y));
	if (t > 0 && boundaries <= cylinder->diameter / 2)
		return (t);
	return (0);
}

static t_vec	get_vec_abc(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	t_ray	ray;
	t_vec	vec_b;
	t_vec	vec_c;

	ray = inter->cam_ray;
	maths.x = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	maths.y = 2 * (ray.dir.x * (ray.origin.x - cylinder->pos.x) + 
		ray.dir.y * (ray.origin.y - cylinder->pos.y));
	maths.z = (ray.origin.x - cylinder->pos.x) * (ray.origin.x - cylinder->pos.x) + 
		(ray.origin.y - cylinder->pos.y) * (ray.origin.y - cylinder->pos.y) - 
		(cylinder->diameter / 2) * (cylinder->diameter / 2);

	return(maths);
}

/* Checks if camera_ray intersects with the side plane (if delta > 0)
 and if the intersection happens inside the cylinder's height */
static float	tube(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	float delta;
	float	t;
	float	t1;
	float	t2;
	float	z1;
	float	z2;

	t = FLT_MAX;

	maths = get_vec_abc(inter, cylinder);

	delta = maths.y * maths.y - 4 * maths.x * maths.z;

	if (delta >= 0) 
	{
		t1 = (-maths.y + sqrt(delta)) / (2 * maths.x);
		t2 = (-maths.y - sqrt(delta)) / (2 * maths.x);

		z1 = inter->cam_ray.origin.z + t1 * inter->cam_ray.dir.z;
		z2 = inter->cam_ray.origin.z + t2 * inter->cam_ray.dir.z;

		if (z1 >= cylinder->pos.z - cylinder->height / 2 && z1 <= cylinder->pos.z + cylinder->height / 2)
		{
			// printf("side 1\n");
			if (t1 > 0)
				t = t1;
		}
		if (z2 >= cylinder->pos.z - cylinder->height / 2 && z2 <= cylinder->pos.z + cylinder->height / 2)
		{
			// printf("side 2\n");
			if (t2 > 0 && t2 < t)
				t = t2;
		}
	}
	if (t != FLT_MAX)
		return (t);
	else
		return (0);
}

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

/*We divide the cylinder into three objects : two planes and a tube.
We then check if the camera_ray intersects with any of these three objects*/
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
	// printf("height = %f\n", cylinder->height);
	// printf("hdiameter = %f\n", cylinder->diameter);
	
	t = closest_t(t_top, t_bottom, t_side);
	if (t > 0)
	{
		inter->obj = cylinder;
		inter->dist = t;
		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
		if (t == t_side)
		{
			// printf("side\n");
			inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
		}
		else if (t == t_top)
		{
			// printf("top\n");
			inter->normal = create_vec(0, 1, 0);
		}
		else if (t == t_bottom)
		{
			// printf("bottom\n");
			inter->normal = create_vec(0, -1, 0);
		}
	}
}
