/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:15:38 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/02 18:22:28 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if the light source is reachable by a straight
line from the point of intersection. We thus iterate through
each object and compare if the distance from the intersection
point is higher than the distance from other intersection points
from other objects. If yes, it means other objects are closer*/


/* t_inter	compute_light_ray(t_inter inter, t_objs *light, t_objs *objects)
{
	t_color	color;
	t_vec l_rgb;
	t_inter interlight;
	t_vec point_to_light;
	t_vec light_dir;
	float dist_light;


	color = inter.obj->color; //pourrait etre envoyé si besoin (norme)
	l_rgb = vec_multiply_float((t_vec){color.bgra[2], color.bgra[1], color.bgra[0]}, light->lightness);
	point_to_light = vec_substract(light->pos, inter.point);
	dist_light = get_norm(point_to_light);
	light_dir = vec_divide(point_to_light, dist_light);
	interlight = closest_intersection((t_ray){inter.point, light_dir}, objects, dist_light);
	interlight.ray.dir = light_dir; //pour norme mais moche!! et ne marche pas je ne sais pourquoi dans l_rgb = vec_multiply_float(l_rgb, ft_fabs(dot_product(light_dir, inter.normal)));

	return(interlight);
} */