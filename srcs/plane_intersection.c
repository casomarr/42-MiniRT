/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:05:16 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/23 16:07:38 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_norm2(t_vec *a, t_data *data)
{
	data->norm = sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

t_vec normalize_vec(t_vec v)
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
//     //get_norm2(&object->position, data);
//     t_vec normal = normalize_vec(object->direction); //direction de la normale du plan
//     ray->discriminant = dot_product(ray->direction, normal);
//     //if (ray->discriminant != 0)
//     if (ray->discriminant > 1*10e-6) // != 0    
//         ray->t = dot_product(vec_substract(object->position, ray->origin), normal) / ray->discriminant;
//     else
//         ray->t = FLT_MAX;
// }

// void    intersection_point_plane(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
// {
//     t_vec intersection_point;
    
//     if (ray->t > 1*10e-6) // != 0
//     {
//         *intersection = true;
//         intersection_point = vec_add(data->ray.origin, vec_multiply_float(data->ray.direction, ray->t));
//         //ici faire transorfmation x et y
//         //multiplier par cosinus 
//         /* t_objs *camera = get_node(data->scene.objs, CAMERA);
//         t_vec gamaprim = create_vec(object->position.x, object->position.y, 0.0);
//         intersection_point.x *= (camera->position.z - object->position.x) / sqrtf(dot_product(vec_substract(gamaprim, camera->position), vec_substract(gamaprim, camera->position))); */
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

	ray->origin = normalize_vec(ray->origin);
	object->position = normalize_vec(object->position);
	distance = vec_substract(ray->origin, object->position);
	b = vec_multiply_float(ray->direction, -1);
	t = (dot_product(distance, object->direction)) / dot_product(b, object->direction);
	if (t > 0.0 && t < data->z_index)
	{
		data->z_index = t;
		data->closest_object = *object;
		data->closest_intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
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
	if (dot_product(object->direction, ray->direction) != 0.0)
	{
		*intersection = true;
		D = dot_product(object->direction, object->position);
		t = (D - object->direction.x * camera->position.x - object->direction.y * \
		camera->position.y - object->direction.z * camera->position.z) / \
		dot_product(object->direction, ray->direction);
		intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
		data->closest_intersection_point = intersection_point;
		data->closest_object = *object;
	}
} */

//calculs Patou en reel
void	intersection_point_plane(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	float	div;
	float	t;
	float	D;
	t_objs	*camera;
	
	camera = get_node(data->scene.objs, CAMERA);
	div = dot_product(object->direction, ray->direction);
	if (div != 0.0)
	{
		D = dot_product(object->direction, object->position);
		t = (D - object->direction.x * camera->position.x - object->direction.y * \
		camera->position.y - object->direction.z * camera->position.z) / div;
		if (t >= 0)
		{
			*intersection = true;
			// data->closest_intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, \
			// dot_product(vec_substract(object->position, ray->origin), object->direction) / div));
			data->closest_intersection_point = vec_multiply_float(vec_add(camera->position, ray->direction), t);
			data->closest_object = *object;
		}
	}
}

//coordonnees reel
t_vec	get_intersection_point_plane(t_data *data, t_objs *object, t_ray *ray)
{
	float	div;
	float	t;
	float	D;
	t_objs	*camera;
	t_vec	intersection_point;
	
	intersection_point = create_vec(0.0, 0.0, 0.0);
	camera = get_node(data->scene.objs, CAMERA);
	div = dot_product(object->direction, ray->direction);
	if (div != 0.0)
	{
		D = dot_product(object->direction, object->position);
		t = (D - object->direction.x * camera->position.x - object->direction.y * \
		camera->position.y - object->direction.z * camera->position.z) / div;
		if (t >= 0)
			data->closest_intersection_point = vec_multiply_float(vec_add(camera->position, ray->direction), t);
			//intersection_point = vec_add(ray->origin, vec_multiply_float(ray->direction, t));
	}
	return(intersection_point);
}
