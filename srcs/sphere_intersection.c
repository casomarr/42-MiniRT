/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/12 14:48:58 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_intersection_sphere(t_objs *object, t_ray *ray)
{
	ray->point.x = dot_product(ray->direction, ray->direction); //norme au carré
	ray->point.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, object->position));
	ray->point.z = dot_product(vec_substract(ray->origin, object->position), vec_substract(ray->origin, object->position)) - powf(object->diameter / 2, 2);
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
			data->intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, ray->t));
			//ici faire transorfmation x et y
			//multiplier par cosinus
			/* t_objs *camera = get_node(data->scene.objs, CAMERA);
			t_vec gamaprim = create_vec(object->position.x, object->position.y, 0.0);
			data->intersection_point.x *= (camera->position.z - object->position.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->position), vec_substract(gamaprim, camera->position))); */
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

/*Checks if the light source is reachable by a straight
line from the point of intersection. We thus iterate through
each object and compare if the distance from the intersection
point is higher than the distance from other intersection points
from other objects. If yes, it means other objects are closer*/
void	check_intersection_light(t_data *data, t_ray *light_ray)
{
	t_objs *light;
	t_objs *object;
	int trigger = 0;
	data->z_index_light = FLT_MAX;
	data->initial_z = 0.0;
	light_ray->t = 0;

	if (light_ray->discriminant >= 0.0)
	{
		light = get_node(data->scene.objs, LIGHT);
		if (light == NULL || light->lightness == 0.0)
		{
			//TODO gerer ce cas et proteger tous les autres get_node
			return ;
		}
		object = data->scene.objs;
		if (light_ray->t > 0)
		{
			while(object)
			{
				if (object->type == SPHERE)
					check_intersection_sphere(object, light_ray);
				// else if (object->type == PLANE)
				// 	check_intersection_plane(object, light_ray);
				// else if (object->type == CYLINDER)
				// 	check_intersection_cylinder(object, light_ray);
				if (light_ray->t > 0) //si intersection avec l'un des objets
				{
					data->intersection_point = vec_add(light_ray->origin, vec_multiply_float(light_ray->direction, light_ray->t));
					if (trigger == 0)
					{
						data->initial_z = light_ray->t;
						trigger = 1;
					}
				}
				if (light_ray->t > 0 && light_ray->t < data->z_index) //light_ray->t > 0 car sinon derriere camera
					data->z_index_light = light_ray->t;
				object = object->next;
			}
		}
	}
	if(data->initial_z == data->z_index_light)
		data->direct_light = true;
}
