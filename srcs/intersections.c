/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:47:22 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/30 13:43:30 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_intersection(bool *intersection, t_data *data, t_objs *sphere)
{
	// printf("intersection BEFORE = %d\n", *intersection);
	
	//calculer ici si le rayon hit the sphere
	//if yes, data->z_index (=closest object) is updated. Initialize it to NULL? (soit a 0,0,0).
	
	//mettre ans une variable data->current_pixel_color la couleur de l'objet intersecte
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
	// exit(1); //sans ça on voit que les nums deviennent infinis
	
	// if (discriminant < 0) //pas besoin de cette condition vu que initialisé à faux et que vrai prime
	// 	intersection = false; //si pas déjà vrai!
	if (discriminant == 0)
		*intersection = true; //en un seul point (sur le bord)
	if (discriminant > 0)
		*intersection = true; //en deux points

	if (discriminant >= 0 && data->z_index < sphere->position.z)
	{
		data->z_index = sphere->position.z;
		data->front_object_color = sphere->color.full;
	}
	// printf("intersection AFTER = %d\n", *intersection);

	
/*	t_vec	ray_location;
	t_vec	tmp_calc;
	
	//ray_location = vecSubstract(data->ray.direction, 2 * data->ray.norm);
	ray_location.x = data->ray.direction.x - (2 * data->ray.norm);
	ray_location.y = data->ray.direction.y - (2 * data->ray.norm);
	ray_location.z = data->ray.direction.z - (2 * data->ray.norm);
	
	// tmp_calc = vecProduct(data->ray.direction, data->ray.norm);
	tmp_calc.x = data->ray.direction.x * data->ray.norm;
	tmp_calc.y = data->ray.direction.y * data->ray.norm;
	tmp_calc.z = data->ray.direction.z * data->ray.norm; 
	
	ray_location = vecProduct(ray_location, tmp_calc); */



/* 	t_vec ray_location;
    t_vec tmp_calc;
    
    // Calculate ray location
    ray_location.x = data->ray.camera_center.x + data->ray.direction.x * data->ray.norm;
    ray_location.y = data->ray.camera_center.y + data->ray.direction.y * data->ray.norm;
    ray_location.z = data->ray.camera_center.z + data->ray.direction.z * data->ray.norm;

    // Calculate tmp_calc using the normalized ray direction
    tmp_calc.x = data->ray.direction.x;
    tmp_calc.y = data->ray.direction.y;
    tmp_calc.z = data->ray.direction.z;
    
    ray_location = vecAdd(ray_location, tmp_calc); // You should use vecSum instead of vecProduct here

    int x = (int)(ray_location.x * WIN_WIDTH);
    int y = (int)(ray_location.y * WIN_HEIGHT);

    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
        printf("Intersection at pixel %d:%d, color %d\n", x, y, data->img.tab[y][x]);

        if (data->img.tab[y][x] != WHITE) // WHITE = BACKGROUND COLOR
            *intersection = true;
    } */

	

/* 	t_vec ray_location;

    // Calculate ray location
    ray_location.x = data->ray.camera_center.x + data->ray.direction.x * data->ray.norm;
    ray_location.y = data->ray.camera_center.y + data->ray.direction.y * data->ray.norm;
    ray_location.z = data->ray.camera_center.z + data->ray.direction.z * data->ray.norm;

    int x = (int)(ray_location.x * WIN_WIDTH);
    int y = (int)(ray_location.y * WIN_HEIGHT); */
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