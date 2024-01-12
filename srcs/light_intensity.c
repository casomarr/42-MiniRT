/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intensity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:55:14 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/12 14:32:21 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	lerp(float ratio, float min, float max) //pour multiplier les couleurs par le brdf
{
	return (min + ratio * (max - min));
}

float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min); //pour éviter noir --> ambient light
	if (value > max)
		return(max);
	return (value);
}
/*Bidirectional Reflectance Distribution Function :
function that takes as parameters the direction of
the ray when entering and leaving the object. If the
angle that we get is narrow, the light intensity will
be higher (more intense).*/
float		brdf(t_data *data)
{
	t_vec	surface_normal;
	t_objs	*ambient;
	float var_brdf;

	surface_normal = vec_substract(data->closest_intersection_point, data->current_object.position);
	if (get_node(data->scene.objs, LIGHT) != NULL && get_node(data->scene.objs, LIGHT)->lightness != 0.0)
	{
		float magnitude = vec_pythagore(surface_normal);
		surface_normal.x /= magnitude;
		surface_normal.y /= magnitude;
		surface_normal.z /= magnitude;
		var_brdf = dot_product(data->light_ray.direction, surface_normal);
		var_brdf = (clamp(var_brdf, -1.0, 1.0) + 1) / 2;
	}
	else
		var_brdf = 0.0;
	ambient = get_node(data->scene.objs, AMBIENT);
	var_brdf = var_brdf + ambient->lightness;
	return var_brdf;
}

