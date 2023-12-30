/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:47:22 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/30 13:58:12 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if the ray intersects with the current sphere.
If yes, checks if there is no other object intersecting
with the ray before it hits the sphere by comparing its
position.z to the z_index that keeps in memory the closest
intersection point (closest to the camera/origin of the ray).
If the spphere is closest, the variables z_index and
front_object_color are updated.*/
void	sphere_intersection(bool *intersection, t_data *data, t_objs *sphere)
{
	//il ne fallait pas utiliser ray.norm ici??
	
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = DotProduct(data->ray.object_direction, data->ray.object_direction);
	b = 2 * DotProduct(data->ray.object_direction, vecSubstract(data->ray.origin, sphere->position));
	c = DotProduct(vecSubstract(data->ray.origin, sphere->position), vecSubstract(data->ray.origin, sphere->position)) - powf(sphere->diameter, 2);

	discriminant = powf(b, 2) - (4 * a * c);

	// printf("a = %f\n", a);
	// printf("b = %f\n", b);
	// printf("c = %f\n", c);
	// printf("discriminant = %f\n", discriminant);
	
	// if (discriminant < 0) //pas besoin de cette condition vu que initialisé à faux et que vrai prime
	// 	intersection = false; //si pas déjà vrai!
	if (discriminant == 0)
		*intersection = true; //en un seul point (sur le bord)
	if (discriminant > 0)
		*intersection = true; //en deux points

	if (discriminant >= 0 && data->z_index < sphere->position.z) /*devrait être l'inverse
	(sphere->position.z < data->z_index) mais alors il faut initialiser z_index à autre chose
	que 0 ou initialiser front_object_color ailleurs, sinon front_object_color ne sera 
	jamais initialisé!*/
	{
		data->z_index = sphere->position.z;
		data->front_object_color = sphere->color.full;
	}
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
	// printf("intersection AVANT = %d\n", intersection); //false = 0
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
	// printf("intersection APRES = %d\n", intersection); //false = 0
	// exit(1);
	return (intersection);
}