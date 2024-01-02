/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intensity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:55:14 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/02 18:22:35 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if the light source is reachable by a straight
line from the point of intersection. If not, it means the
current pixel is in the shadow.*/
// bool	direct_light(t_data *data)
// {
	
// 	///test
// 	(void)data;
// 	return (true); //bleu
// 	// return (false); //blanc
// }

/*The closer the object is to the light source, the
higher is the light intensity reflected on the object.
This equation is called Inverse Square Law.*/
int	distance_light_object(t_data *data)
{
/* 	t_vec	result;
	t_vec	intersection;
	t_objs	*light;
	float	distance;

	intersection = create_vec(data->x, data->y, data->z_index);
	light = get_node(data->scene.objs, LIGHT);
	result = vecSubstract(light->position, intersection);
	result = vecSqrt(result);
	distance = sqrtf(result.x + result.y + result.z);

	//soit juste : distance_to_light = vecMagnitude(vecSubstract(vecAdd(ray->origin, vecMultiplyFloat(ray->direction, ray->t)), ray->origin));
	// printf("distance = %f\n", distance);
	
	return distance; */

	// printf("distance = %f\n", data->light_distance);
	return (data->light_distance);
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
	return (-1);
}
