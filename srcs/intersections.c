/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:10:10 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/23 16:09:43 by casomarr         ###   ########.fr       */
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
			//check_intersection_sphere(object, &data->ray);
			intersection_point_sphere(&intersection, data, object, &data->ray);
		}
		else if (object->type == PLANE)
		{
			//check_intersection_plane(object, &data->ray, data);
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
			//check_intersection_sphere(object, &data->ray);
			intersection_point_sphere(&intersection, data, object, &data->ray);
		}
		object = object->next;
	}
	return (intersection);
}

/* float calculate_t_value(t_vec intersection_point, t_vec light_position, t_vec light_direction)
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
} */


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
	float	initial_distance;
	float	current_distance;
	t_vec	current_intersection_point;
	t_objs *light;
	t_objs *object;
	t_vec	empty_vec; ///demandr a antoone comment passer la norme sans ca

	empty_vec = create_vec(0.0, 0.0, 0.0);
	data->direct_light = true;
	object = data->scene.objs;
	light = get_node(data->scene.objs, LIGHT);
	if (light == NULL || light->lightness == 0.0)
	{
		//TODO gerer ce cas et proteger tous les autres get_node
		return ;
	}

	initial_distance = get_norm3(vec_substract(light->position, data->closest_intersection_point));	
	while(object)
	{
		current_intersection_point = create_vec(0.0, 0.0, 0.0);
		current_distance = 0.0;
		if (object->type == SPHERE)
		{
			current_intersection_point = get_intersection_point_sphere(object, light_ray, data);
			if (vec_compare(current_intersection_point, empty_vec) == false) //if intersection
			{
				// current_distance = get_norm3(vec_substract(current_intersection_point, data->closest_intersection_point));
				current_distance = get_norm3(vec_substract(data->closest_intersection_point, current_intersection_point));
				//printf("current distance, `%f`, initial distance, `%f`\n", current_distance, initial_distance);
				if (current_distance < initial_distance)
				{
					data->direct_light = false;
					return ;
				}
			}
		}
/* 		else if (object->type == PLANE)
		{
			current_intersection_point = get_intersection_point_plane(data, object, light_ray);
			if (vec_compare(current_intersection_point, empty_vec) == false) //if intersection
			{
				printf("here 1\n");
				current_distance = get_norm3(vec_substract(data->closest_intersection_point, current_intersection_point));
				if (current_distance < initial_distance)
				{
					printf("here 2\n");
					data->direct_light = false;
					return ;
				}
			}
		} */
		/* else if (object->type == CYLINDER)
		{
			
			if (current_distance < initial_distance)
			{
				data->direct_light = false;
				return ;
			}
		} */
		object = object->next;
	}
}