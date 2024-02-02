/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:05:16 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/30 17:46:34 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_norm2(t_vec *a, t_data *data)
{
	data->norm = sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

t_vec vec_normalize(t_vec v)
{
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    t_vec result;

    if (length != 0)
    {
        result.x = v.x / length;
        result.y = v.y / length;
        result.z = v.z / length;
    }
    else
    {
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }

    return result;
}

// void	check_intersection_plane(t_objs *object, t_ray *ray, t_data *data)
// {

// }

// void    check_intersection_plane(t_objs *object, t_ray *ray, t_data *data)
// {
//     (void)data;
//     //get_norm2(&object->pos, data);
//     t_vec normal = vec_normalize(object->dir); //dir de la normale du plan
//     ray->discriminant = dot_product(ray->dir, normal);
//     //if (ray->discriminant != 0)
//     if (ray->discriminant > 1*10e-6) // != 0
//         ray->t = dot_product(vec_substract(object->pos, ray->origin), normal) / ray->discriminant;
//     else
//         ray->t = FLT_MAX;
// }

// void    intersection_point_plane(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
// {
//     t_vec intersection_point;

//     if (ray->t > 1*10e-6) // != 0
//     {
//         *intersection = true;
//         intersection_point = vec_add(data->ray.origin, vec_multiply_float(data->ray.dir, ray->t));
//         //ici faire transorfmation x et y
//         //multiplier par cosinus
//         /* t_objs *camera = get_node(data->scene.objs, CAMERA);
//         t_vec gamaprim = create_vec(object->pos.x, object->pos.y, 0.0);
//         intersection_point.x *= (camera->pos.z - object->pos.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->pos), vec_substract(gamaprim, camera->pos))); */
//         if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
//         {
//             data->z_index = ray->t;
//             data->closest_intersection_point = intersection_point;
//             data->closest_object = *object;
//         }
//     }
// }


/* void	intersection_point_plane(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	t_vec	distance;
	t_vec	b;
	float	t;

	ray->origin = vec_normalize(ray->origin);
	object->pos = vec_normalize(object->pos);
	distance = vec_substract(ray->origin, object->pos);
	b = vec_multiply_float(ray->dir, -1);
	t = (dot_product(distance, object->dir)) / dot_product(b, object->dir);
	if (t > 0.0 && t < data->z_index)
	{
		data->z_index = t;
		data->closest_object = *object;
		data->closest_intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, t));
		*intersection = true;
	}
} */

/* //calculs de Patou en non reel
void	intersection_point_plane(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	t_vec	intersection_point;
	t_objs	*camera;
	float	t;
	float 	D;

	camera = get_node(data->scene.objs, CAMERA);
	if (dot_product(object->dir, ray->dir) != 0.0)
	{
		*intersection = true;
		D = dot_product(object->dir, object->pos);
		t = (D - object->dir.x * camera->pos.x - object->dir.y * \
		camera->pos.y - object->dir.z * camera->pos.z) / \
		dot_product(object->dir, ray->dir);
		intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, t));
		data->closest_intersection_point = intersection_point;
		data->closest_object = *object;
	}
} */

//calculs Patou en reel
void	intersection_point_plane(t_inter *inter, t_objs *plane)
{
	float	div;
	float	t;
	float	dot;
	t_ray	ray;

	ray = inter->cam_ray;
	div = dot_product(plane->dir, ray.dir);
	if (div != 0.0)
	{
		dot = dot_product(plane->dir, plane->pos);
		t = (dot - plane->dir.x * ray.origin.x - plane->dir.y * \
		ray.origin.y - plane->dir.z * ray.origin.z) / div;
		if (t > 0 && t < inter->dist)
		{
			inter->dist = t;
			inter->obj = plane;
			inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
			if (dot_product(plane->dir, inter->cam_ray.dir) < 0)
				inter->normal = plane->dir;
			else
				inter->normal = vec_multiply_float(plane->dir, -1);
		}
	}
}

//coordonnees reel
/* t_vec	get_intersection_point_plane(t_data *data, t_objs *object, t_ray *ray)
{
	float	div;
	float	t;
	float	D;
	t_objs	*camera;
	t_vec	intersection_point;

	intersection_point = create_vec(0.0, 0.0, 0.0);
	camera = get_node(data->scene.objs, CAMERA);
	div = dot_product(object->dir, ray->dir);
	if (div != 0.0)
	{
		D = dot_product(object->dir, object->pos);
		t = (D - object->dir.x * camera->pos.x - object->dir.y * \
		camera->pos.y - object->dir.z * camera->pos.z) / div;
		if (t >= 0)
			data->closest_intersection_point = vec_multiply_float(vec_add(camera->pos, ray->dir), t);
			//intersection_point = vec_add(ray->origin, vec_multiply_float(ray->dir, t));
	}
	return(intersection_point);
} */
