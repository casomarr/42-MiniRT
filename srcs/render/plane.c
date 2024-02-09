/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:05:16 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/09 17:19:21 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersection_point_plane(t_inter *inter, t_objs *plane)
{
	float	div;
	float	t;
	float	dot;
	t_ray	ray;

	ray = inter->ray;
	div = dot_product(plane->dir, ray.dir);
	if (div != 0.0)
	{
		dot = dot_product(plane->dir, plane->pos);
		t = (dot - plane->dir.x * ray.origin.x - plane->dir.y * \
		ray.origin.y - plane->dir.z * ray.origin.z) / div;
		if (t > 0. && t < inter->dist)
		{
			inter->dist = t;
			inter->obj = plane;
			inter->point = vec_add(inter->ray.origin, \
			vec_multiply_float(inter->ray.dir, t));
			if (dot_product(plane->dir, inter->ray.dir) < 0.)
				inter->normal = plane->dir;
			else
				inter->normal = vec_multiply_float(plane->dir, -1);
		}
	}
}
