/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intensity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:55:14 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/05 16:31:00 by amugnier         ###   ########.fr       */
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
float	distance_light_object(t_data *data)
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

	//DOIT RENDRE UN NUM ENTRE 0 ET 1
	return (data->light_distance);

//donne cercle rouge
	// (void)data;
	// return(1);


/* 	float	constant_attenuation = 1.0;
	float	linear_attenuation = 0.01;
	float	quadratic_attenuation = 0.001;
	float	attenuation;
	float	brightness;
	float	max_attenuation = 0.5; //après tests mettre à 0.1 et 0.9?
	float	min_attenuation = 0.9;

	attenuation = 1 / (constant_attenuation + (linear_attenuation * data->light_distance) + (quadratic_attenuation * powf(data->light_distance, 2)));
	// printf("attenuation = %f\n", attenuation);
	brightness = (max_attenuation - min_attenuation) / ((attenuation - min_attenuation));
	// printf("brightness = %f\n", brightness);

	return (brightness); */
}
/*Bidirectional Reflectance Distribution Function :
function that takes as parameters the direction of
the ray when entering and leaving the object. If the
angle that we get is narrow, the light intensity will
be higher (more intense).*/
float	brdf(t_data *data)
{
//get_norm() ne marche que pour t_ray -->le changer pour  que ça colle avec tout

	t_vec	surface_normal;

	surface_normal = vecSubstract(data->current_object.position, data->closest_intersection_point);

	float magnitude = vecMagnitude(surface_normal);
	surface_normal.x /= magnitude;
	surface_normal.y /= magnitude;
	surface_normal.z /= magnitude;

	float brdf = DotProduct(data->ray.direction, surface_normal);

	//pas sûre que mes protections soient utiles
	if (brdf < 0.0)
		brdf = 0.0; //pour éviter noir --> ambient light
	if (brdf > 1.0)
		brdf = 1.0;

	t_objs	*ambient;
	ambient = get_node(data->scene.objs, AMBIENT);
	brdf = brdf + ambient->lightness; //dans determine_pixel color devient noir qd meme c'est chelou
	// printf("brdf = %f\n", brdf);

	return brdf;


	// (void)data;
	// return (1); //test pour ne pas le prendre en compte comme ça on multiplie * 1
}

/*Returns the intensity of the shadowing (by how much does
the pixel color has to be toned down).
Constant attenuation : constant factor by which the light
intensity decreases regardless of the distance.
Linear attenuation : light intensity diminishes as the distance
between the light source and the intersection point increases.
Quadratic attenuation : idem as linear attenuation but in a
way that makes it more realistic.
*/
float	shadows(t_data *data)
{
	/*
	attenuation = 1 / constant + linear * distance + quadratic * distance2
	brightness = max_attenuation − min_attenuation / attenuation − min_attenuation
	final_color = brightness * object_color
	*/

	float	constant_attenuation = 0.1;
	float	linear_attenuation = 0.007;
	float	quadratic_attenuation = 0.01;
	float	attenuation;
	float	brightness;
	float	max_attenuation = 0.1;
	float	min_attenuation = 0.9;

	attenuation = 1 / (constant_attenuation + (linear_attenuation * data->light_distance) + (quadratic_attenuation * powf(data->light_distance, 2)));
	// printf("attenuation = %f\n", attenuation);
	brightness = (max_attenuation - min_attenuation) / ((attenuation - min_attenuation));
	// printf("brightness = %f\n", brightness);

	return (brightness);
}
