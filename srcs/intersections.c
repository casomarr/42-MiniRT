/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:47:22 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/30 16:43:18 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if the ray intersects with the current sphere.
If yes, checks if there is no other object intersecting
with the ray before it hits the sphere by comparing its
position.z to the z_index that keeps in memory the closest
intersection point (closest to the camera/origin of the ray).
If the spphere is closest, the variables z_index and
front_object_color are updated.
The discriminant determines how many times the ray intersects
with the sphere at this (x, y) point (it can pass through the
sphere and therefore intersect with it at two different z depths).
discriminant < 0 --> no intersection
discriminant = 0 --> intersects with the edge of the sphere
discriminant > 0 --> intersects the sphere twice (= it passes
through the "middle" of the sphere)*/
void	sphere_intersection(bool *intersection, t_data *data, t_objs *sphere)
{
	//il ne fallait pas utiliser ray.norm ici??
	
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;

	a = DotProduct(data->ray.object_direction, data->ray.object_direction);
	b = 2 * DotProduct(data->ray.object_direction, vecSubstract(data->ray.origin, sphere->position));
	c = DotProduct(vecSubstract(data->ray.origin, sphere->position), vecSubstract(data->ray.origin, sphere->position)) - powf(sphere->diameter, 2);
	
	discriminant = powf(b, 2) - (4 * a * c);
	if (discriminant == 0)
		*intersection = true; //en un seul point (sur le bord)
	if (discriminant > 0)
		*intersection = true; //en deux points

	//on choisit le point d'intersection le plus proche de la camera
	if ((-b + sqrtf(discriminant)) / (2 * a) < (-b - sqrtf(discriminant)) / (2 * a))
		t = (-b + sqrtf(discriminant)) / (2 * a);
	else
		t = (-b - sqrtf(discriminant)) / (2 * a);
	
	data->intersection_point = vecAdd(data->ray.origin, vecMultiplyFloat(data->ray.object_direction, t));
	
	// if (discriminant >= 0 && data->z_index < sphere->position.z) /*devrait être l'inverse
	// (sphere->position.z < data->z_index) mais alors il faut initialiser z_index à autre chose
	// que 0 ou initialiser front_object_color ailleurs, sinon front_object_color ne sera 
	// jamais initialisé!*/
	if (discriminant >= 0 && t < data->z_index)
	{
		data->z_index = data->intersection_point.z;
		data->front_object_color = sphere->color.full;
	}

	//pour test je l'initialise ici :
	data->front_object_color = sphere->color.full;
}

/*Checks if the current ray intersects with each of the objects
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
	data->z_index = 0;
	while (object)
	{
		if (object->type == SPHERE)
			sphere_intersection(&intersection, data, object);
		/* else if (object->type == CYLINDER)
			cylinder_intersection(&intersection, data);
		else if (object->type == PLANE)
			plane_intersection(&intersection, data); */
		object = object->next;
	}
	return (intersection);
}