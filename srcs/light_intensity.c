/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intensity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:55:14 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/03 17:41:53 by octonaute        ###   ########.fr       */
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

//donne cercle rouge avec interieur noir
	// printf("distance = %f\n", data->light_distance);
	return (data->light_distance);

//donne cercle rouge
	// (void)data;
	// return(1);
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
float	shadows(t_data *data)
{
	/*
	attenuation = 1 / constant + linear * distance + quadratic * distance2
	brightness = max_attenuation − min_attenuation / attenuation − min_attenuation
	final_color = brightness * object_color
	*/
	
	float	constant_attenuation = 1.0;
	float	linear_attenuation = 0.01;
	float	quadratic_attenuation = 0.001;
	float	attenuation;
	float	brightness;
	float	max_attenuation = 0.3; //après tests mettre à 0.1 et 0.9?
	float	min_attenuation = 0.7;

	attenuation = 1 / (constant_attenuation + (linear_attenuation * data->light_distance) + (quadratic_attenuation * powf(data->light_distance, 2)));
	// printf("attenuation = %f\n", attenuation);
	brightness = (max_attenuation - min_attenuation) / ((attenuation - min_attenuation));
	// printf("brightness = %f\n", brightness);

	return (brightness);

	// (void)data;
	// return(0.5);
}
