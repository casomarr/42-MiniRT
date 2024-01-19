/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/19 18:17:15 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* void	check_intersection_sphere_light(t_objs *object, t_ray *light_ray)
{
	t_vec	calc;
	t_vec intersection_point;
	
	calc.x = dot_product(light_ray->direction, light_ray->direction); //norme au carré
	calc.y = 2 * dot_product(light_ray->direction, vec_substract(light_ray->origin, object->position));
	calc.z = dot_product(vec_substract(light_ray->origin, object->position), vec_substract(light_ray->origin, object->position)) - powf(object->diameter / 2, 2);
	light_ray->discriminant = powf(calc.y, 2) - (4 * calc.x * calc.z); // b2 - 4ac
	if (light_ray->discriminant >= 0)
	{
		if ((-calc.y + sqrtf(light_ray->discriminant)) / (2 * calc.x) < (-calc.y - sqrtf(light_ray->discriminant)) / (2 * calc.x))
			light_ray->t = (-calc.y + sqrtf(light_ray->discriminant)) / (2 * calc.x);
		else
			light_ray->t = (-calc.y - sqrtf(light_ray->discriminant)) / (2 * calc.x);
		
		intersection_point = vec_add(light_ray->origin, vec_multiply_float(light_ray->direction, light_ray->t));
		
		t_vec direction = vec_substract(intersection_point, object->position);
		float	sphere_normal = get_norm3(direction);
		t_vec 	new_intersect = vec_add_float(intersection_point, sphere_normal / 10000);
	}
} */

void	check_intersection_sphere(t_objs *sphere, t_ray *ray)
{
	t_vec	calc;
	
	calc.x = dot_product(ray->direction, ray->direction); //norme au carré
	calc.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, sphere->position));
	calc.z = dot_product(vec_substract(ray->origin, sphere->position), vec_substract(ray->origin, sphere->position)) - powf(sphere->diameter / 2, 2);
	// calc.x = dot_product(ray->direction, ray->direction); //norme au carré  //TEST
	// calc.y = 2 * dot_product(ray->direction, vec_substract(sphere->position, ray->origin)); //TEST
	// calc.z = dot_product(vec_substract(sphere->position, ray->origin), vec_substract(sphere->position, ray->origin)) - powf(sphere->diameter / 2, 2); //TEST
	ray->discriminant = powf(calc.y, 2) - (4 * calc.x * calc.z); // b2 - 4ac
	if (ray->discriminant >= 0)
	{
		// if (ray->discriminant == 0)
		// 	printf("OUI\n");
		if ((-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x) < (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x))
			ray->t = (-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x);
		else
			ray->t = (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x);
	}
}

void	intersection_point_sphere(bool *intersection, t_data *data, t_objs *sphere, t_ray *ray)
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
			t_vec gamaprim = create_vec(sphere->position.x, sphere->position.y, 0.0);
			intersection_point.x *= (camera->position.z - sphere->position.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->position), vec_substract(gamaprim, camera->position))); */
			if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
			{
				data->z_index = ray->t;
				data->closest_intersection_point = intersection_point;
				data->closest_object = *sphere;
			}
		}
	}
}

void	further_point_from_same_object_of_intersection_point(t_objs *sphere, t_ray *ray)
{
	ray->point.x = dot_product(ray->direction, ray->direction); //norme au carré
	ray->point.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, sphere->position));
	ray->point.z = dot_product(vec_substract(ray->origin, sphere->position), vec_substract(ray->origin, sphere->position)) - powf(sphere->diameter / 2, 2);
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

/* void	intersection_with_light_from_closest_point_from_camera(t_objs *object, t_ray *ray)
{
	ray->point.x = dot_product(ray->direction, ray->direction); //norme au carré
	ray->point.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, object->position));
	ray->point.z = dot_product(vec_substract(ray->origin, object->position), vec_substract(ray->origin, object->position)) - powf(object->diameter / 2, 2);
	ray->discriminant = powf(ray->point.y, 2) - (4 * ray->point.x * ray->point.z); // b2 - 4ac
	if (ray->discriminant >= 0)
	{
		//calculer distance from both points to camera. ray->t takes the closest one

		float	tA = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
		float	tB = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
		t_vec	intersectionA = vec_add(ray->origin, vec_multiply_float(ray->direction, tA));
		t_vec	intersectionB = vec_add(ray->origin, vec_multiply_float(ray->direction, tB));
		float	distance_A_camera = ray->origin.z - intersectionA.z;
		float	distance_B_camera = ray->origin.z - intersectionB.z;
		
		if (distance_A_camera < distance_B_camera)
			ray->t = tA;
		else
			ray->t = tB;
	}
} */
