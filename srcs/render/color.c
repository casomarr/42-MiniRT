/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/06 18:16:37 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_from_rgb(t_uint8 r, t_uint8 g, t_uint8 b)
{
	t_color	rgb;

	rgb.full = 0;
	rgb.bgra[0] = b;
	rgb.bgra[1] = g;
	rgb.bgra[2] = r;
	return (rgb);
}

t_color	color_from_vec(t_vec v)
{
	return (color_from_rgb(v.x, v.y, v.z));
}

/*Calculates the color of the intersected object given the
ambient light's intensity and color.
The render_ambiant option allows to render prettiest objects shadow-wise.*/
t_vec	get_ambi_rgb(t_inter inter, t_objs *ambient, t_data *data, t_ray ray)
{
	t_color	color;
	t_vec	ambi_rgb;

	color = inter.obj->color;
	ambi_rgb = (t_vec){color.bgra[2], color.bgra[1], color.bgra[0]};
	ambi_rgb = vec_min(ambi_rgb, (t_vec){ambient->color.bgra[2], \
	ambient->color.bgra[1], ambient->color.bgra[0]});
	ambi_rgb = vec_multiply_float(ambi_rgb, ambient->lightness);
	if (data->render_ambiant == true)
		ambi_rgb = vec_multiply_float(ambi_rgb, \
		ft_fabs(dot_product(ray.dir, inter.normal)));
	return (ambi_rgb);
}

/*Checks if the light source is reachable by a straight
line from the point of intersection. We thus iterate through
each object and compare if the distance from the intersection
point is higher than the distance from other intersection points
from other objects. If yes, it means other objects are closer*/
t_vec	get_light_rgb(t_inter inter, t_objs *light, t_objs *objs, \
t_inter *interlight)
{
	t_color	color;
	t_vec	l_rgb;
	t_vec	point_to_light;
	t_vec	light_dir;
	float	dist_light;

	color = inter.obj->color;
	l_rgb = vec_multiply_float((t_vec){color.bgra[2], \
	color.bgra[1], color.bgra[0]}, light->lightness);
	point_to_light = vec_substract(light->pos, inter.point);
	dist_light = get_norm(point_to_light);
	light_dir = vec_divide(point_to_light, dist_light);
	*interlight = closest_intersection((t_ray){inter.point, \
	light_dir}, objs, dist_light);
	l_rgb = vec_multiply_float(l_rgb, \
	ft_fabs(dot_product(light_dir, inter.normal)));
	return (l_rgb);
}
