/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:10:10 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/17 18:28:23 by octonaute        ###   ########.fr       */
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
    t_vec light_to_intersection = vec_substract(intersection_point, light_position);

    // Calculate the magnitude of the vector (length of the vector)
    float distance_from_light_to_intersection = vec_pythagore(light_to_intersection);

    // Calculate the magnitude of the direction of the light ray
    float light_direction_magnitude = vec_pythagore(light_direction);

    // Calculate the parameter 't' along the light ray
    float t_value = distance_from_light_to_intersection / light_direction_magnitude;

    return t_value;
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
	float	initial_t;
	// initial_t = FLT_MAX;
	data->light_ray.discriminant = 0.0;
	
	light = get_node(data->scene.objs, LIGHT);
	if (light == NULL || light->lightness == 0.0)
	{
		//TODO gerer ce cas et proteger tous les autres get_node
		return ;
	}
	data->direct_light = true;
	
	//initial intersection object's t for light ray
	// if (data->closest_object.type == SPHERE)
		//intersection_with_light_from_closest_point_from_camera(&data->closest_object, &data->ray);
		initial_t = calculate_t_value(data->closest_intersection_point, light->position, light_ray->direction); //TODO: returns the "t" from closest intersection point from camera from light
		// check_intersection_sphere(&data->closest_object, light_ray);
	// initial_t = light_ray->t;
	
	object = data->scene.objs;
	while(object)
	{
		light_ray->t = 0.0f;
		if (object->type == SPHERE)
			check_intersection_sphere(object, light_ray);
			// further_point_from_same_object_of_intersection_point(object, light_ray);
/* 		else if (object->type == PLANE) //si en commentaire le plan alors pas de bruit!
			check_intersection_plane(object, light_ray, data);
		else if (object->type == CYLINDER)
			check_intersection_cylinder(object, light_ray); */
		if (light_ray->t > 0.0f && light_ray->t < initial_t) //si intersection avec l'un des objets  //light_ray->t > 0 car sinon derriere camera
		{
			//condition avec != au lieu de < : ombres sur plans apparaissent
			// printf("aqui\n");
			data->direct_light = false;
		}
		object = object->next;
	}
}
