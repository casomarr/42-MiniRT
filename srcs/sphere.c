/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:58:18 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/29 19:09:01 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* void	check_intersection_sphere_light(t_objs *object, t_ray *light_ray)
{
	t_vec	calc;
	t_vec intersection_point;
	
	calc.x = dot_product(light_ray->dir, light_ray->dir); //norme au carré
	calc.y = 2 * dot_product(light_ray->dir, vec_substract(light_ray->origin, object->pos));
	calc.z = dot_product(vec_substract(light_ray->origin, object->pos), vec_substract(light_ray->origin, object->pos)) - powf(object->diameter / 2, 2);
	light_ray->discriminant = powf(calc.y, 2) - (4 * calc.x * calc.z); // b2 - 4ac
	if (light_ray->discriminant >= 0)
	{
		if ((-calc.y + sqrtf(light_ray->discriminant)) / (2 * calc.x) < (-calc.y - sqrtf(light_ray->discriminant)) / (2 * calc.x))
			light_ray->t = (-calc.y + sqrtf(light_ray->discriminant)) / (2 * calc.x);
		else
			light_ray->t = (-calc.y - sqrtf(light_ray->discriminant)) / (2 * calc.x);
		
		intersection_point = vec_add(light_ray->origin, vec_multiply_float(light_ray->dir, light_ray->t));
		
		t_vec dir = vec_substract(intersection_point, object->pos);
		float	sphere_normal = get_norm(dir);
		t_vec 	new_intersect = vec_add_float(intersection_point, sphere_normal / 10000);
	}
} */

// void	check_intersection_sphere(t_objs *sphere, t_ray *ray)
// {
// 	t_vec	calc;
	
// 	calc.x = dot_product(ray->dir, ray->dir); //norme au carré
// 	calc.y = 2 * dot_product(ray->dir, vec_substract(ray->origin, sphere->pos));
// 	calc.z = dot_product(vec_substract(ray->origin, sphere->pos), vec_substract(ray->origin, sphere->pos)) - powf(sphere->diameter / 2, 2);
// 	// calc.x = dot_product(ray->dir, ray->dir); //norme au carré  //TEST
// 	// calc.y = 2 * dot_product(ray->dir, vec_substract(sphere->pos, ray->origin)); //TEST
// 	// calc.z = dot_product(vec_substract(sphere->pos, ray->origin), vec_substract(sphere->pos, ray->origin)) - powf(sphere->diameter / 2, 2); //TEST
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
// 			intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, ray->t));
// 			//ici faire transorfmation x et y
// 			//multiplier par cosinus
// 			/* t_objs *camera = get_node(data->scene.objs, CAMERA);
// 			t_vec gamaprim = create_vec(sphere->pos.x, sphere->pos.y, 0.0);
// 			intersection_point.x *= (camera->pos.z - sphere->pos.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->pos), vec_substract(gamaprim, camera->pos))); */
// 			if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
// 			{
// 				intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, ray->t));
// 				t_vec dir = vec_substract(intersection_point, sphere->pos);
// 				float	sphere_normal = get_norm(dir);
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
// 	ray->point.x = dot_product(ray->dir, ray->dir); //norme au carré
// 	ray->point.y = 2 * dot_product(ray->dir, vec_substract(ray->origin, sphere->pos));
// 	ray->point.z = dot_product(vec_substract(ray->origin, sphere->pos), vec_substract(ray->origin, sphere->pos)) - powf(sphere->diameter / 2, 2);
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
	ray->point.x = dot_product(ray->dir, ray->dir); //norme au carré
	ray->point.y = 2 * dot_product(ray->dir, vec_substract(ray->origin, object->pos));
	ray->point.z = dot_product(vec_substract(ray->origin, object->pos), vec_substract(ray->origin, object->pos)) - powf(object->diameter / 2, 2);
	ray->discriminant = powf(ray->point.y, 2) - (4 * ray->point.x * ray->point.z); // b2 - 4ac
	if (ray->discriminant >= 0)
	{
		//calculer distance from both points to camera. ray->t takes the closest one

		float	tA = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
		float	tB = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
		t_vec	intersectionA = vec_add(ray->origin, vec_multiply_float(ray->dir, tA));
		t_vec	intersectionB = vec_add(ray->origin, vec_multiply_float(ray->dir, tB));
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
	
	a = dot_product(ray->dir, ray->dir); //norme au carré

	camera = get_node(data->scene.objs, CAMERA);
	crp2 = vec_multiply_float(vec_multiply(camera->pos, ray->dir), 2);
	b = crp2.x - ray->dir.x * (sphere->pos.x * 2) + crp2.y - \
	ray->dir.y * (sphere->pos.y * 2) + crp2.z - ray->dir.z * \
	(sphere->pos.z * 2);
	
	dcsp = vec_multiply_float(vec_multiply(camera->pos, sphere->pos), 2);
	c = powf(camera->pos.x, 2) + powf(sphere->pos.x, 2) - dcsp.x + \
	powf(camera->pos.y, 2) + powf(sphere->pos.y, 2) - dcsp.y + \
	powf(camera->pos.z, 2) + powf(sphere->pos.z, 2) - dcsp.z - \
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
			data->closest_intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, t));
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

static t_vec	get_vec_abc(t_inter *inter, t_objs *sphere)
{
	t_vec	maths;
	t_ray	ray;
	t_vec	vec_b;
	t_vec	vec_c;

	ray = inter->cam_ray;

	maths.x = dot_product(ray.dir, ray.dir);

	vec_b = vec_multiply_float(vec_multiply(ray.origin, ray.dir), 2.);
	vec_b = vec_substract(vec_b, vec_multiply(ray.dir, vec_multiply_float(sphere->pos, 2.)));
	maths.y = vec_b.x + vec_b.y + vec_b.z;

	vec_c = vec_multiply_float(vec_multiply(ray.origin, sphere->pos), 2.);
	maths.z = powf(ray.origin.x, 2.) + powf(sphere->pos.x, 2.) - vec_c.x + \
	powf(ray.origin.y, 2.) + powf(sphere->pos.y, 2.) - vec_c.y + \
	powf(ray.origin.z, 2.) + powf(sphere->pos.z, 2.) - vec_c.z - \
	powf(sphere->diameter / 2., 2.);

	return(maths);
}

void	intersection_point_sphere(t_inter *inter, t_objs *sphere)
{
	t_vec	maths;
	float	delta;
	float	t;
	
	maths = get_vec_abc(inter, sphere);
	delta = maths.y * maths.y - 4. * maths.x * maths.z; // b2 - 4ac
	if (delta > 0.)
	{
		//vérifier si le plus petit est inférieur à 0
		if ((-maths.y + sqrtf(delta)) / (2. * maths.x) < (-maths.y - sqrtf(delta)) / (2. * maths.x))
 			t = (-maths.y + sqrtf(delta)) / (2. * maths.x);
 		else
 			t = (-maths.y - sqrtf(delta)) / (2. * maths.x);
	}
	else if (delta == 0.)
		t = -maths.y / (2. * maths.x);
	if (delta >= 0 && t > 0. && t < inter->dist)
	{
		inter->dist = t;
		inter->obj = sphere;
		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
		inter->normal = vec_normalize(vec_substract(inter->point, sphere->pos));
		// inter->point = vec_add(inter->point, vec_multiply_float(inter->normal, 0.000001)); //Décaler point de la norme de la normale à la sphère * 0.00000001
	}
}

/* t_vec	get_intersection_point_sphere(t_objs *object, t_ray *ray, t_data *data)
{
	(void)data;
	
	t_vec	calc;
	float 	delta;
	t_vec	intersection_point;
	float	t;
	
	calc.x = dot_product(ray->dir, ray->dir); //norme au carré
	calc.y = 2 * dot_product(ray->dir, vec_substract(ray->origin, object->pos));
	calc.z = dot_product(vec_substract(ray->origin, object->pos), vec_substract(ray->origin, object->pos)) - powf(object->diameter / 2, 2);
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
		intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, t));
		t_vec dir = vec_substract(intersection_point, object->pos);
		float	sphere_normal = get_norm(dir);
		intersection_point = vec_add_float(intersection_point, sphere_normal / 100000);
	}
	return (intersection_point);
} */

/* t_vec	get_intersection_point_sphere(t_objs *sphere, t_ray *ray, t_data *data)
{
	//ne marche pas car on doit changer l'origine du rayon
	//ai change camera->pos par light->pos
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

	a = dot_product(ray->dir, ray->dir); //norme au carré

	light = get_node(data->scene.objs, LIGHT);
	crp2 = vec_multiply_float(vec_multiply(light->pos, ray->dir), 2);
	b = crp2.x - ray->dir.x * (sphere->pos.x * 2) + crp2.y - \
	ray->dir.y * (sphere->pos.y * 2) + crp2.z - ray->dir.z * \
	(sphere->pos.z * 2);

	dcsp = vec_multiply_float(vec_multiply(light->pos, sphere->pos), 2);
	c = powf(light->pos.x, 2) + powf(sphere->pos.x, 2) - dcsp.x + \
	powf(light->pos.y, 2) + powf(sphere->pos.y, 2) - dcsp.y + \
	powf(light->pos.z, 2) + powf(sphere->pos.z, 2) - dcsp.z - \
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
		intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, t));
	return(intersection_point); //no intersection
} */
