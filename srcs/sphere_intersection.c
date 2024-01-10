/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/10 14:30:04 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_intersection_sphere(t_objs *object, t_ray *ray)
{
	ray->point.x = DotProduct(ray->direction, ray->direction); //norme au carré
	ray->point.y = 2 * DotProduct(ray->direction, vecSubstract(ray->origin, object->position));
	ray->point.z = DotProduct(vecSubstract(ray->origin, object->position), vecSubstract(ray->origin, object->position)) - powf(object->diameter / 2, 2);
	ray->discriminant = powf(ray->point.y, 2) - (4 * ray->point.x * ray->point.z); // b2 - 4ac
	if (ray->discriminant >= 0)
	{
		if ((-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x) < (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x))
			ray->t = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
		else
			ray->t = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
	}
}

void	intersection_point_sphere(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	if (ray->discriminant >= 0)
	{
		*intersection = true;
		if (ray->t > 0)
		{
			data->intersection_point = vecAdd(data->ray.origin, vecMultiplyFloat(data->ray.direction, ray->t));
			//ici faire transorfmation x et y
			//multiplier par cosinus 
			/* t_objs *camera = get_node(data->scene.objs, CAMERA);
			t_vec gamaprim = create_vec(object->position.x, object->position.y, 0.0);
			data->intersection_point.x *= (camera->position.z - object->position.x) / sqrtf(DotProduct(vecSubstract(gamaprim, camera->position), vecSubstract(gamaprim, camera->position))); */
			if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
			{
				// printf("z_index updated\n");
				data->z_index = ray->t; // et non data->intersection_point.z car peut etre négatif vu que 3D
				data->closest_intersection_point = data->intersection_point;
				data->closest_object_type = object->type;
				data->current_object = *object;
				data->front_object_color = object->color.full;
			}
		}
	}
}
