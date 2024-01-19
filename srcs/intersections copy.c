/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:10:10 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/19 15:50:45 by casomarr         ###   ########.fr       */
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

// float calculate_t_value(t_vec intersection_point, t_vec light_position, t_vec light_direction)
// {
// 	// Calculate the vector from the light position to the intersection point
// 	t_vec light_to_intersection = vec_substract(intersection_point, light_position);

// 	// Calculate the magnitude of the vector (length of the vector)
// 	float distance_from_light_to_intersection = vec_pythagore(light_to_intersection);

// 	// Calculate the magnitude of the direction of the light ray
// 	float light_direction_magnitude = vec_pythagore(light_direction);

// 	// Calculate the parameter 't' along the light ray
// 	float t_value = distance_from_light_to_intersection / light_direction_magnitude;

// 	return t_value;
// }

float calculate_t_value(t_vec ray_origin, t_vec intersection_point, t_vec ray_direction)
{
	// Calculate the vector from the ray origin to the intersection point
	t_vec origin_to_intersection = vec_substract(intersection_point, ray_origin);

	// Calculate the dot product of the above vector and the ray direction
	float t_value = dot_product(origin_to_intersection, ray_direction);

	return t_value;
}

float	get_norm3(t_vec vec)
{
	return(sqrtf(vec.x * vec.x + \
				vec.y * vec.y + \
				vec.z * vec.z));
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

	object = data->scene.objs;

	//direction du centre de la pshere vers le point d'intersection
	t_vec direction = vec_substract(data->closest_intersection_point, object->position);
	// printf("data->closest_intersection_point.x = %f, data->closest_intersection_point.y = %f, data->closest_intersection_point.z = %f\n", data->closest_intersection_point.x, data->closest_intersection_point.y, data->closest_intersection_point.z);
	float	sphere_normal = get_norm3(direction);
	t_vec 	new_intersect = vec_add_float(data->closest_intersection_point, (sphere_normal / 1000.0));
	// printf("new_intersect.x = %f, new_intersect.y = %f, new_intersect.z = %f\n", new_intersect.x, new_intersect.y, new_intersect.z);
	
	
	initial_t = calculate_t_value(new_intersect, light->position, light_ray->direction);
	
	//initial_t = calculate_t_value(data->closest_intersection_point, light->position, light_ray->direction);
	// check_intersection_sphere(&data->closest_object, light_ray);
	// initial_t = light_ray->t;

	// //normale du point d'intersection (calcul different pour chaque type d'objet)
	// float intersection_norm = get_norm3(data->closest_intersection_point);
/* 	// vecteurA = intersection - sphere->position
	t_vec	vectorA = vec_substract(data->closest_intersection_point, data->closest_object.position);
	//normaliser vecteurA
	float	variateur = get_norm3(vectorA);
	//rajouter un pourcentage de la normale de vecteur A au point d'intersection dans la ligne suivante
	initial_t = calculate_t_value(vec_multiply_float(data->closest_intersection_point, variateur * 0.2), light->position, light_ray->direction); */
	
	while(object)
	{
		light_ray->t = 0.0f;
		if (object->type == SPHERE)
			check_intersection_sphere(object, light_ray); //c'est ca qui cree les ombres et ne cree pas le bruit
			// check_intersection_sphere(&data->closest_object, light_ray);
			// further_point_from_same_object_of_intersection_point(object, light_ray);
		else if (object->type == PLANE) //si en commentaire le plan alors pas de bruit!
			check_intersection_plane(object, light_ray, data);
		// else if (object->type == CYLINDER)
		// 	check_intersection_cylinder(object, light_ray);
		if (light_ray->t > 0.0f && light_ray->t < initial_t) //si intersection avec l'un des objets  //light_ray->t > 0 car sinon derriere camera
		{
			//condition avec != au lieu de < : ombres sur plans apparaissent
			// printf("aqui\n");
			data->direct_light = false;
		}
		object = object->next;
	}
}
