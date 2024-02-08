/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_check_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:36:56 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/08 15:40:06 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Checks if the ray intersects with an infinite plane (top or bottom).
If discriminant > 0. it ensure the plane is not parallel to the ray */
static float	intersect_ray_plane(t_ray ray, t_vec planePoint, \
t_vec planeNormal)
{
	float	t;
	float	discriminant;
	t_vec	raytoplane;

	discriminant = dot_product(planeNormal, ray.dir);
	if (fabs(discriminant) > 0.)
	{
		raytoplane = vec_substract(planePoint, ray.origin);
		t = dot_product(raytoplane, planeNormal) / discriminant;
		return (t);
	}
	return (0);
}

/* Calculates the variables a, b and c (maths.x, maths.y and maths.z)
to calculate delta further on */
static t_vec	get_abc(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	t_vec	a;
	t_vec	b;
	t_vec	dist;
	float	radiussquared;

	a = vec_substract(inter->ray.dir, vec_multiply_float(cylinder->dir, \
	dot_product(inter->ray.dir, cylinder->dir)));
	dist = vec_substract(inter->ray.origin, cylinder->pos);
	b = vec_substract(dist, vec_multiply_float(cylinder->dir, \
	dot_product(dist, cylinder->dir)));
	radiussquared = cylinder->diameter / 2 * cylinder->diameter / 2;
	maths.x = dot_product(a, a);
	maths.y = 2 * dot_product(a, b);
	maths.z = dot_product(b, b) - radiussquared;
	return (maths);
}

/* Checks if the ray intersects with the tube (if delta > 0)
and if the intersection happens inside the cylinder's height */
float	check_hit_side(t_inter *inter, t_objs *cylinder)
{
	float	delta;
	float	t;
	float	y;
	t_vec	maths;
	float	distdotdir;

	maths = get_abc(inter, cylinder);
	distdotdir = dot_product(vec_substract(inter->ray.origin, \
	cylinder->pos), cylinder->dir);
	delta = maths.y * maths.y - 4 * maths.x * maths.z;
	if (delta >= 0.)
	{
		t = (-maths.y - sqrtf(delta)) / (2 * maths.x);
		y = distdotdir + t * dot_product(inter->ray.dir, cylinder->dir);
		if ((y >= 0. && y <= cylinder->height) && t > 0.)
			return (t);
		t = (-maths.y + sqrtf(delta)) / (2 * maths.x);
		y = distdotdir + t * dot_product(inter->ray.dir, cylinder->dir);
		if ((y >= 0. && y <= cylinder->height) && t > 0. && t < FLT_MAX)
			return (t);
	}
	return (0);
}

/* Checks if the ray intersects with the top plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
float	check_hit_captop(t_inter *inter, t_objs *cylinder)
{
	t_vec	captocenter;
	float	ttop;

	captocenter = vec_add(cylinder->pos, \
	vec_multiply_float(cylinder->dir, cylinder->height));
	ttop = intersect_ray_plane(inter->ray, captocenter, cylinder->dir);
	if (vec_length(vec_substract(vec_add(inter->ray.origin, \
	vec_multiply_float(inter->ray.dir, ttop)), captocenter)) \
	<= cylinder->diameter / 2)
		return (ttop);
	return (0.);
}

/* Checks if the ray intersects with the bottom plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
float	check_hit_capbottom(t_inter *inter, t_objs *cylinder)
{
	float	tbottom;

	tbottom = intersect_ray_plane(inter->ray, cylinder->pos, cylinder->dir);
	if (vec_length(vec_substract(vec_add(inter->ray.origin, \
	vec_multiply_float(inter->ray.dir, tbottom)), cylinder->pos)) \
	<= cylinder->diameter / 2)
		return (tbottom);
	return (0.);
}
