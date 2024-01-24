/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/24 21:11:50 by octonaute        ###   ########.fr       */
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

// void	check_intersection_sphere(t_objs *sphere, t_ray *ray)
// {
// 	t_vec	calc;
	
// 	calc.x = dot_product(ray->direction, ray->direction); //norme au carré
// 	calc.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, sphere->position));
// 	calc.z = dot_product(vec_substract(ray->origin, sphere->position), vec_substract(ray->origin, sphere->position)) - powf(sphere->diameter / 2, 2);
// 	// calc.x = dot_product(ray->direction, ray->direction); //norme au carré  //TEST
// 	// calc.y = 2 * dot_product(ray->direction, vec_substract(sphere->position, ray->origin)); //TEST
// 	// calc.z = dot_product(vec_substract(sphere->position, ray->origin), vec_substract(sphere->position, ray->origin)) - powf(sphere->diameter / 2, 2); //TEST
// 	ray->discriminant = powf(calc.y, 2) - (4 * calc.x * calc.z); // b2 - 4ac
// 	if (ray->discriminant >= 0)
// 	{
// 		// if (ray->discriminant == 0)
// 		// 	printf("OUI\n");
// 		if ((-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x) < (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x))
// 			ray->t = (-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x);
// 		else
// 			ray->t = (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x);
// 	}
// }

// void	intersection_point_sphere(bool *intersection, t_data *data, t_objs *sphere, t_ray *ray)
// {
// 	t_vec intersection_point;
	
// 	if (ray->discriminant >= 0)
// 	{
// 		*intersection = true;
// 		if (ray->t > 0)
// 		{
// 			intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, ray->t));
// 			//ici faire transorfmation x et y
// 			//multiplier par cosinus
// 			/* t_objs *camera = get_node(data->scene.objs, CAMERA);
// 			t_vec gamaprim = create_vec(sphere->position.x, sphere->position.y, 0.0);
// 			intersection_point.x *= (camera->position.z - sphere->position.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->position), vec_substract(gamaprim, camera->position))); */
// 			if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
// 			{
// 				intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, ray->t));
// 				t_vec direction = vec_substract(intersection_point, sphere->position);
// 				float	sphere_normal = get_norm3(direction);
// 				intersection_point = vec_add_float(intersection_point, sphere_normal / 100000);
			
// 				data->z_index = ray->t;
// 				data->closest_intersection_point = intersection_point;
// 				data->closest_object = *sphere;
// 			}
// 		}
// 	}
// }

// void	further_point_from_same_object_of_intersection_point(t_objs *sphere, t_ray *ray)
// {
// 	ray->point.x = dot_product(ray->direction, ray->direction); //norme au carré
// 	ray->point.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, sphere->position));
// 	ray->point.z = dot_product(vec_substract(ray->origin, sphere->position), vec_substract(ray->origin, sphere->position)) - powf(sphere->diameter / 2, 2);
// 	ray->discriminant = powf(ray->point.y, 2) - (4 * ray->point.x * ray->point.z); // b2 - 4ac
// 	if (ray->discriminant >= 0)
// 	{
// 		// if (ray->discriminant == 0)
// 		// 	printf("OUI\n");
// 		if ((-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x) > (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x))
// 			ray->t = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
// 		else
// 			ray->t = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
// 	}
// }

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

/* void	intersection_point_sphere(bool *intersection, t_data *data, t_objs *sphere, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	t_vec crp2;
	t_vec dcsp;
	t_objs	*camera;
	
	a = dot_product(ray->direction, ray->direction); //norme au carré

	camera = get_node(data->scene.objs, CAMERA);
	crp2 = vec_multiply_float(vec_multiply(camera->position, ray->direction), 2);
	b = crp2.x - ray->direction.x * (sphere->position.x * 2) + crp2.y - \
	ray->direction.y * (sphere->position.y * 2) + crp2.z - ray->direction.z * \
	(sphere->position.z * 2);
	
	dcsp = vec_multiply_float(vec_multiply(camera->position, sphere->position), 2);
	c = powf(camera->position.x, 2) + powf(sphere->position.x, 2) - dcsp.x + \
	powf(camera->position.y, 2) + powf(sphere->position.y, 2) - dcsp.y + \
	powf(camera->position.z, 2) + powf(sphere->position.z, 2) - dcsp.z - \
	powf(sphere->diameter / 2, 2);

	delta = b * b - 4 * a * c; // b2 - 4ac
	if (delta >= 0)
	{
		if ((-b + sqrtf(delta)) / (2 * a) > (-b - sqrtf(delta)) / (2 * a))
 			t = (-b + sqrtf(delta)) / (2 * a);
 		else
 			t = (-b - sqrtf(delta)) / (2 * a);
	}
	else if (delta == 0)
		t = -b / (2 * a);
	else
		return ; //no intersection
	if (t > 0)
	{
		*intersection = true;
		if (t > 0 && t < data->z_index) //t > 0 car sinon derriere camera
		{
			data->z_index = t;
			//intersection : calcul a moi, pas patou
			data->closest_intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
			//patou calculait la normale ici
			data->closest_object = *sphere;
		}
	}
} */

// code patou reel

float	ft_fabs(float f)
{
	if (f < 0)
		return (f * -1.);
	return (f);
}

t_vec	get_vec_abc()
{
	//TODO: diviser intersection_point_sphere en plusieurs fonctions pour norme
	// + essayer de faire marcher les plans
}

void	intersection_point_sphere(t_inter *inter, t_objs *sphere)
{
	t_ray	ray;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	t_vec	vecb;
	t_vec cpr2;
	t_vec dcsp;
	// t_objs	*camera;
	// float	t1;
	// float	t2;
	
	ray = inter->cam_ray;
	a = dot_product(ray.dir, ray.dir); //norme au carré
	cpr2 = vec_multiply_float(vec_multiply(ray.origin, ray.dir), 2.);
	// vecb = cpr2 - dir * sphere.dpos
	vecb = vec_substract(cpr2, vec_multiply(ray.dir, vec_multiply_float(sphere->position, 2.)));
	b = vecb.x + vecb.y + vecb.z;
	// b = crp2.x - ray->direction.x * (sphere->position.x * 2) + crp2.y - \
	// ray->direction.y * (sphere->position.y * 2) + crp2.z - ray->direction.z * \
	// (sphere->position.z * 2);
	
	dcsp = vec_multiply_float(vec_multiply(ray.origin, sphere->position), 2.);
	c = powf(ray.origin.x, 2.) + powf(sphere->position.x, 2.) - dcsp.x + \
	powf(ray.origin.y, 2.) + powf(sphere->position.y, 2.) - dcsp.y + \
	powf(ray.origin.z, 2.) + powf(sphere->position.z, 2.) - dcsp.z - \
	powf(sphere->diameter / 2., 2.);

	delta = b * b - 4. * a * c; // b2 - 4ac
	if (delta > 0.)
	{
		//vérifier si le plus petit est inférieur à 0
		if ((-b + sqrtf(delta)) / (2. * a) < (-b - sqrtf(delta)) / (2. * a))
 			t = (-b + sqrtf(delta)) / (2. * a);
 		else
 			t = (-b - sqrtf(delta)) / (2. * a);
	}
	else if (delta == 0.)
		t = -b / (2. * a);
	else
		return ; //no intersection
	if (t > 0. && t < inter->dist)
	{
		inter->dist = t;
		inter->obj = sphere;
		//Décaler point de la norme de la normale à la sphère * 0.00000001
		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
		inter->normal = normalize_vec(vec_substract(inter->point, sphere->position));
		inter->point = vec_add(inter->point, vec_multiply_float(inter->normal, 0.000001));
		// *intersection = true;
		// if (t > 0 && t < data->z_index) //t > 0 car sinon derriere camera
		// {
		// 	data->z_index = t;
		// 	//intersection : calcul a moi, pas patou
		// 	data->closest_intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
		// 	//patou calculait la normale ici
		// 	data->closest_object = *sphere;
	}
}

/* t_vec	get_intersection_point_sphere(t_objs *object, t_ray *ray, t_data *data)
{
	(void)data;
	
	t_vec	calc;
	float 	delta;
	t_vec	intersection_point;
	float	t;
	
	calc.x = dot_product(ray->direction, ray->direction); //norme au carré
	calc.y = 2 * dot_product(ray->direction, vec_substract(ray->origin, object->position));
	calc.z = dot_product(vec_substract(ray->origin, object->position), vec_substract(ray->origin, object->position)) - powf(object->diameter / 2, 2);
	delta = powf(calc.y, 2) - (4 * calc.x * calc.z); // b2 - 4ac
	t = 0.0;
	intersection_point = create_vec(0.0, 0.0, 0.0);
	if (delta >= 0)
	{
		if ((-calc.y + sqrtf(delta)) / (2 * calc.x) < (-calc.y - sqrtf(delta)) / (2 * calc.x))
			t = (-calc.y + sqrtf(delta)) / (2 * calc.x);
		else
			t = (-calc.y - sqrtf(delta)) / (2 * calc.x);
	}
	if (t > 0)
	{
		intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
		t_vec direction = vec_substract(intersection_point, object->position);
		float	sphere_normal = get_norm3(direction);
		intersection_point = vec_add_float(intersection_point, sphere_normal / 100000);
	}
	return (intersection_point);
} */

/* t_vec	get_intersection_point_sphere(t_objs *sphere, t_ray *ray, t_data *data)
{
	//ne marche pas car on doit changer l'origine du rayon
	//ai change camera->position par light->position
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;
	t_vec crp2;
	t_vec dcsp;
	t_objs	*light;
	t_vec	intersection_point;
	
	intersection_point = create_vec(0.0, 0.0, 0.0);

	a = dot_product(ray->direction, ray->direction); //norme au carré

	light = get_node(data->scene.objs, LIGHT);
	crp2 = vec_multiply_float(vec_multiply(light->position, ray->direction), 2);
	b = crp2.x - ray->direction.x * (sphere->position.x * 2) + crp2.y - \
	ray->direction.y * (sphere->position.y * 2) + crp2.z - ray->direction.z * \
	(sphere->position.z * 2);

	dcsp = vec_multiply_float(vec_multiply(light->position, sphere->position), 2);
	c = powf(light->position.x, 2) + powf(sphere->position.x, 2) - dcsp.x + \
	powf(light->position.y, 2) + powf(sphere->position.y, 2) - dcsp.y + \
	powf(light->position.z, 2) + powf(sphere->position.z, 2) - dcsp.z - \
	powf(sphere->diameter / 2, 2);

	delta = b * b - 4 * a * c; // b2 - 4ac
	if (delta > 0)
	{
		if ((-b + sqrtf(delta)) / (2 * a) < (-b - sqrtf(delta)) / (2 * a))
 			t = (-b + sqrtf(delta)) / (2 * a);
 		else
 			t = (-b - sqrtf(delta)) / (2 * a);
	}
	else if (delta == 0)
		t = -b / (2 * a);
	if (delta >= 0 && t > 0) //t tjrs < a 0!!
		intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
	return(intersection_point); //no intersection
} */