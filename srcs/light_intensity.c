/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intensity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:55:14 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/29 19:04:30 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*The closer the object is to the light source, the
higher is the light intensity reflected on the object.
This equation is called Inverse Square Law.*/
int	distance_light_object(t_data *data)
{
	t_vec	result;
	t_vec	intersection;
	t_objs	*light;
	float	distance;

	intersection = create_vec(data->x, data->y, data->z_index);
	light = get_node(data->scene.objs, LIGHT);
	result = vecSubstract(light->position, intersection);
	result = vecSqrt(result);
	distance = sqrtf(result.x + result.y + result.z);
	//printf("distance = %d\n", distance);
	return distance;
}
/*Bidirectional Reflectance Distribution Function :
function that takes as parameters the direction of
the ray when entering and leaving the object. If the
angle that we get is narrow, the light intensity will
be higher (more intense).*/
int	brdf(t_data *data)
{
	//utilise la norme je crois

	//test
	(void)data;
	return (1); //test pour ne pas le prendre en compte comme ça on multiplie * 1
}

/*Returns the intensity of the shadowing (by how much does
the pixel color has to be toned down)*/
int	shadows(t_data *data)
{
	(void)data;
	return (1);
}
