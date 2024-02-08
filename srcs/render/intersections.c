/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:10:10 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/08 15:52:28 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if a given ray intersects with each of the objects
present in the scene. Every time an intersection occurs,
inter->distance is updated to keep in memory what is the closest
object that intersects with the ray, so that our image doesn't show
the "hidden" objects.*/
t_inter	closest_intersection(t_ray ray, t_objs *object, float dist)
{
	t_inter	inter;

	inter.ray = ray;
	inter.dist = dist;
	inter.obj = NULL;
	while (object)
	{
		if (object->type == SPHERE)
			intersection_point_sphere(&inter, object);
		else if (object->type == PLANE)
			intersection_point_plane(&inter, object);
		else if (object->type == CYLINDER)
			intersection_point_cylinder(&inter, object);
		object = object->next;
	}
	if (inter.obj)
		inter.point = vec_add(inter.point, \
		vec_multiply_float(inter.normal, 0.0005));
	return (inter);
}
