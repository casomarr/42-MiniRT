/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:05:16 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/12 18:39:42 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_norm2(t_vec *a, t_data *data)
{
	data->norm = sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

void	check_intersection_plan(t_objs *object, t_ray *ray, t_data *data)
{
	(void)data;
	//get_norm2(&object->position, data);
	t_vec normal = object->direction; //direction de la normale du plan
	ray->discriminant = dot_product(ray->direction, normal);
	if (ray->discriminant != 0)
	{	
		ray->t = dot_product(vec_substract(object->position, ray->origin), normal) / ray->discriminant;
	}
	else
		ray->t = FLT_MAX;
}

void	intersection_point_plan(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	t_vec intersection_point;
	
	if (ray->t > 1*10e-6)
	{
		*intersection = true;
		intersection_point = vec_add(data->ray.origin, vec_multiply_float(data->ray.direction, ray->t));
		//ici faire transorfmation x et y
		//multiplier par cosinus 
		/* t_objs *camera = get_node(data->scene.objs, CAMERA);
		t_vec gamaprim = create_vec(object->position.x, object->position.y, 0.0);
		intersection_point.x *= (camera->position.z - object->position.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->position), vec_substract(gamaprim, camera->position))); */
		if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
		{
			data->z_index = ray->t;
			data->closest_intersection_point = intersection_point;
			data->closest_object = *object;
		}
	}
}