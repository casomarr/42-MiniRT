/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:10:10 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/19 18:18:52 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if the current camera ray intersects with each of the objects
present in the scene. Every time an intersection occurs, 
data->z_index is updated to keep in memory what is the closest
object that intersects with the ray, so that our image doesn't show
the "hidden" objects.*/
bool	intersection(t_data *data)
{
	bool	intersection;
	t_objs	*object;

	object = data->scene.objs;
	intersection = false;
	data->z_index = FLT_MAX;
	data->closest_intersection_point = create_vec(0.0, 0.0, 0.0);
	while (object)
	{
		if (object->type == SPHERE)
		{
			check_intersection_sphere(object, &data->ray);
			intersection_point_sphere(&intersection, data, object, &data->ray);
		}
		else if (object->type == PLANE)
		{
			check_intersection_plane(object, &data->ray, data);
			intersection_point_plane(&intersection, data, object, &data->ray);
		}
		else if (object->type == CYLINDER) //fait apparaitre un bout de plan de droite en haut ovalé
		{
			check_intersection_cylinder(object, &data->ray);
			intersection_point_cylinder(&intersection, data, object, &data->ray);
		}
		else if (object->type == LIGHT) //temporaire pour afficher lumiere
		{
			t_objs *light = get_node(data->scene.objs, LIGHT);
			light->diameter = 1.5;
			light->color.argb[0] = 0;
			light->color.argb[1] = 255;
			light->color.argb[2] = 255;
			check_intersection_sphere(object, &data->ray);
			intersection_point_sphere(&intersection, data, object, &data->ray);
		}
		object = object->next;
	}
	return (intersection);
}

float calculate_t_value(t_vec intersection_point, t_vec light_position, t_vec light_direction)
{
	// Calculate the vector from the light position to the intersection point
	// t_vec light_to_intersection = vec_substract(intersection_point, light_position);
	t_vec light_to_intersection = vec_substract(light_position, intersection_point); //TEST //ne change rien

	// Calculate the magnitude of the vector (length of the vector)
	float distance_from_light_to_intersection = vec_pythagore(light_to_intersection);

	// Calculate the magnitude of the direction of the light ray
	float light_direction_magnitude = vec_pythagore(light_direction);

	// Calculate the parameter 't' along the light ray
	float t_value = distance_from_light_to_intersection / light_direction_magnitude;

	return t_value;
}


float	get_norm3(t_vec vec)
{
	return(sqrtf(vec.x * vec.x + \
				vec.y * vec.y + \
				vec.z * vec.z));
}

bool	vec_compare(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (true);
	return (false);
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
	
	light = get_node(data->scene.objs, LIGHT);
	if (light == NULL || light->lightness == 0.0)
	{
		//TODO gerer ce cas et proteger tous les autres get_node
		return ;
	}
	data->direct_light = true;
	object = data->scene.objs;
	t_vec	current_intersection;
	float	current_t;

	//direction du centre de la pshere vers le point d'intersection
	t_vec	direction = vec_substract(data->closest_intersection_point, object->position);
	// t_vec	direction = vec_substract(data->closest_intersection_point, light->position); //TEST //ne change rien
	float	sphere_normal = get_norm3(direction);
	t_vec	initial_intersect = vec_add_float(data->closest_intersection_point, (sphere_normal / 100000.0));
	float initial_t = calculate_t_value(initial_intersect, light->position, light_ray->direction);
	// float initial_t = calculate_t_value(light->position, initial_intersect, light_ray->direction); //TEST

	//float initial_t = calculate_t_value(data->closest_intersection_point, light->position, light_ray->direction);
	
	while(object)
	{
		light_ray->t = 0.0;
		current_intersection = create_vec(0.0, 0.0, 0.0);
		if (object->type == SPHERE)
		{
			check_intersection_sphere(object, light_ray);
			if (light_ray->discriminant >= 0)
				if (light_ray->t > 0)
				{
					current_intersection = vec_add(light_ray->origin, vec_multiply_float(light_ray->direction, light_ray->t));
					direction = vec_substract(current_intersection, object->position);
					// direction = vec_substract(data->closest_intersection_point, light->position); //TEST //ne change rien
					sphere_normal = get_norm3(direction);
					current_intersection = vec_add_float(current_intersection, (sphere_normal / 100000.0));
					current_t = calculate_t_value(current_intersection, light->position, light_ray->direction);
					// current_t = calculate_t_value(light->position, initial_intersect, light_ray->direction); //TEST

				}
		
		}
		else if (object->type == PLANE)
			check_intersection_plane(object, light_ray, data);
		else if (object->type == CYLINDER)
			check_intersection_cylinder(object, light_ray);
		if (light_ray->t > 0 && light_ray->t < initial_t) //si intersection avec l'un des objets  //light_ray->t > 0 car sinon derriere camera
		{
			data->direct_light = false;
			break;
		}
		object = object->next;
	}
	// if (vec_compare(current_intersection, data->closest_intersection_point) == false) //si intersection avec l'un des objets  //light_ray->t > 0 car sinon derriere camera
	// 		data->direct_light = false;
}
