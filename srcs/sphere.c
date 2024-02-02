/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/02 18:16:40 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	get_vec_abc(t_inter *inter, t_objs *sphere)
{
	t_vec	maths;
	t_ray	ray;
	t_vec	vec_b;
	t_vec	vec_c;

	ray = inter->ray;

	maths.x = dot_product(ray.dir, ray.dir);

	vec_b = vec_multiply_float(vec_multiply(ray.origin, ray.dir), 2.);
	vec_b = vec_substract(vec_b, vec_multiply(ray.dir, vec_multiply_float(sphere->pos, 2.)));
	maths.y = vec_b.x + vec_b.y + vec_b.z;

	vec_c = vec_multiply_float(vec_multiply(ray.origin, sphere->pos), 2.);
	maths.z = powf(ray.origin.x, 2.) + powf(sphere->pos.x, 2.) - vec_c.x + \
	powf(ray.origin.y, 2.) + powf(sphere->pos.y, 2.) - vec_c.y + \
	powf(ray.origin.z, 2.) + powf(sphere->pos.z, 2.) - vec_c.z - \
	powf(sphere->diameter / 2., 2.);

	return(maths);
}

void	intersection_point_sphere(t_inter *inter, t_objs *sphere)
{
	t_vec	maths;
	float	delta;
	float	t;
	
	maths = get_vec_abc(inter, sphere);
	delta = maths.y * maths.y - 4. * maths.x * maths.z; // b2 - 4ac
	if (delta > 0.)
	{
		//vérifier si le plus petit est inférieur à 0
		if ((-maths.y + sqrtf(delta)) / (2. * maths.x) < (-maths.y - sqrtf(delta)) / (2. * maths.x))
 			t = (-maths.y + sqrtf(delta)) / (2. * maths.x);
 		else
 			t = (-maths.y - sqrtf(delta)) / (2. * maths.x);
	}
	else if (delta == 0.)
		t = -maths.y / (2. * maths.x);
	if (delta >= 0 && t > 0. && t < inter->dist)
	{
		inter->dist = t;
		inter->obj = sphere;
		inter->point = vec_add(inter->ray.origin, vec_multiply_float(inter->ray.dir, t));
		inter->normal = vec_normalize(vec_substract(inter->point, sphere->pos));
	}
}
