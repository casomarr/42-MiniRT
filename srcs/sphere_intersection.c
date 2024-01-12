/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/12 18:47:35 by casomarr         ###   ########.fr       */
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
		// if (ray->discriminant == 0)
		// 	printf("OUI\n");
		if ((-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x) < (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x))
			ray->t = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
		else
			ray->t = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
	}
}

void	intersection_point_sphere(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	t_vec intersection_point;
	
	if (ray->discriminant >= 0)
	{
		*intersection = true;
		if (ray->t > 0)
		{
			intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, ray->t));
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
}

void	further_point_from_same_object_of_intersection_point(t_objs *object, t_ray *ray)
{
	ray->point.x = dot_product(ray->direction, ray->direction); //norme au carré
	ray->point.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, object->position));
	ray->point.z = dot_product(vec_substract(ray->origin, object->position), vec_substract(ray->origin, object->position)) - powf(object->diameter / 2, 2);
	ray->discriminant = powf(ray->point.y, 2) - (4 * ray->point.x * ray->point.z); // b2 - 4ac
	if (ray->discriminant >= 0)
	{
		// if (ray->discriminant == 0)
		// 	printf("OUI\n");
		if ((-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x) > (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x))
			ray->t = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
		else
			ray->t = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
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
	float	initial_z; 
	initial_z = FLT_MAX;
	
	light = get_node(data->scene.objs, LIGHT);
	if (light == NULL || light->lightness == 0.0)
	{
		//TODO gerer ce cas et proteger tous les autres get_node
		return ;
	}
	
	//initial intersection object's t for light ray
	if (data->closest_object.type == SPHERE)
		check_intersection_sphere(&data->closest_object, light_ray);
	initial_z = light_ray->t;
	
	object = data->scene.objs;
	while(object)
	{
		light_ray->t = 0.0f;
		if (object->type == SPHERE)
			//check_intersection_sphere(object, light_ray);
			further_point_from_same_object_of_intersection_point(object, light_ray);
		// else if (object->type == PLANE)
		// 	check_intersection_plane(object, light_ray);
		// else if (object->type == CYLINDER)
		// 	check_intersection_cylinder(object, light_ray);
		if (light_ray->t > 0 && light_ray->t != initial_z) //si intersection avec l'un des objets  //light_ray->t > 0 car sinon derriere camera
		{
			(void)trigger;
			data->direct_light = true; //sont inverses
		}
		object = object->next;
	}
}

