/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:36:56 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/08 15:41:33 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the closest intersection distance */
static float	min_over_zero(float tside, float ttop, float tbottom)
{
	float	minval;

	minval = FLT_MAX;
	if (tside > 0. && tside < minval)
		minval = tside;
	if (ttop > 0. && ttop < minval)
		minval = ttop;
	if (tbottom > 0. && tbottom < minval)
		minval = tbottom;
	if (minval != FLT_MAX)
		return (minval);
	else
		return (0);
}

/* Divides the cylinder into three objects : two planes and a tube.
Then checks if the camera_ray intersects with any of these three objects */
void	intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
{
	float	tside;
	float	ttop;
	float	tbottom;
	float	tmin;

	tside = check_hit_side(inter, cylinder);
	ttop = check_hit_captop(inter, cylinder);
	tbottom = check_hit_capbottom(inter, cylinder);
	tmin = min_over_zero(tside, ttop, tbottom);
	if (tmin > 0. && tmin < inter->dist)
	{
		inter->obj = cylinder;
		inter->dist = tmin;
		inter->point = vec_add(inter->ray.origin, \
		vec_multiply_float(inter->ray.dir, tmin));
		if (tmin == tside)
			inter->normal = vec_normalize(vec_substract(vec_substract \
			(inter->point, cylinder->pos), vec_multiply_float(cylinder->dir, \
			dot_product(vec_substract(inter->point, cylinder->pos), \
			cylinder->dir))));
		else if (tmin == tbottom)
				inter->normal = vec_negate(cylinder->dir);
		else if (tmin == ttop)
			inter->normal = cylinder->dir;
	}
}
