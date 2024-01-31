/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:09:52 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/31 18:26:55 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec RotateByDir(t_vec dir_origin, t_vec dir_dest, t_vec p)
{
	t_vec r;

	r = vec_normalize(vec_product(dir_origin, p));
	return (vec_product(dir_dest, r));
}

/* Checks if camera_ray intersects with the upper plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
static float	upper_plane(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	boundaries;

	t = (cylinder->pos.z + cylinder->height / 2 - inter->cam_ray.origin.z) / inter->cam_ray.dir.z;
	boundaries = sqrtf((inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) * \
	(inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) + \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y) * \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y));
	if (t > 0 && boundaries <= cylinder->diameter / 2)
		return (t);
	return (0);
}

/* Checks if camera_ray intersects with the bottom plane (if t > 0)
 and if the intersection happens inside the cylinder's diameter */
static float	bottom_plane(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	boundaries;

	t = (cylinder->pos.z - cylinder->height / 2 - inter->cam_ray.origin.z) / inter->cam_ray.dir.z;
	boundaries = sqrtf((inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) * \
	(inter->cam_ray.origin.x + t * inter->cam_ray.dir.x - cylinder->pos.x) + \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y) * \
	(inter->cam_ray.origin.y + t * inter->cam_ray.dir.y - cylinder->pos.y));
	if (t > 0 && boundaries <= cylinder->diameter / 2)
		return (t);
	return (0);
}

/* t_vec vec_cross(t_vec a, t_vec b) {
    t_vec result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

static t_vec	rotate_to_z_axis(t_vec vec, t_vec axis)
{
    // Normalize the axis
    t_vec axis_normalized = vec_normalize(axis);

    // Calculate the cross product of the axis and the z-axis
    t_vec cross = vec_cross(axis_normalized, (t_vec){0, 0, 1});

    // Calculate the dot product of the axis and the z-axis
    float dot = dot_product(axis_normalized, (t_vec){0, 0, 1});

    // Calculate the rotation matrix
    float rotation_matrix[3][3] = {
        {dot + cross.x * cross.x * (1 - dot), cross.x * cross.y * (1 - dot) - cross.z, cross.x * cross.z * (1 - dot) + cross.y},
        {cross.y * cross.x * (1 - dot) + cross.z, dot + cross.y * cross.y * (1 - dot), cross.y * cross.z * (1 - dot) - cross.x},
        {cross.z * cross.x * (1 - dot) - cross.y, cross.z * cross.y * (1 - dot) + cross.x, dot + cross.z * cross.z * (1 - dot)}
    };

    // Multiply the vector by the rotation matrix
    t_vec rotated_vec = {
        rotation_matrix[0][0] * vec.x + rotation_matrix[0][1] * vec.y + rotation_matrix[0][2] * vec.z,
        rotation_matrix[1][0] * vec.x + rotation_matrix[1][1] * vec.y + rotation_matrix[1][2] * vec.z,
        rotation_matrix[2][0] * vec.x + rotation_matrix[2][1] * vec.y + rotation_matrix[2][2] * vec.z
    };

    return rotated_vec;
}

static t_vec	transform_ray_origin(t_vec ray_origin, t_vec cylinder_pos, t_vec cylinder_dir)
{
    // Translate the ray origin so that the cylinder's base is at the origin
    t_vec translated_origin = vec_substract(ray_origin, cylinder_pos);

    // Rotate the translated origin to align the cylinder with the z-axis
    t_vec rotated_origin = rotate_to_z_axis(translated_origin, cylinder_dir);

    return rotated_origin;
}

static t_vec	transform_ray_direction(t_vec ray_dir, t_vec cylinder_dir)
{
    // Rotate the ray direction to align the cylinder with the z-axis
    t_vec rotated_direction = rotate_to_z_axis(ray_dir, cylinder_dir);

    return rotated_direction;
} */

static t_vec	get_vec_abc(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	t_ray	ray;
	t_vec	vec_b;
	t_vec	vec_c;

/////////////////
/* 	// Transform the ray's origin and direction to align the cylinder with the z-axis
    t_vec transformed_origin = transform_ray_origin(inter->cam_ray.origin, cylinder->pos, cylinder->dir);
    t_vec transformed_direction = transform_ray_direction(inter->cam_ray.dir, cylinder->dir);

    ray.origin = transformed_origin;
    ray.dir = transformed_direction; */


/* 	t_vec rotated_origin = RotateByDir(cylinder->dir, cylinder->dir, vec_substract(inter->cam_ray.origin, cylinder->pos));
	t_vec rotated_direction = RotateByDir(cylinder->dir, cylinder->dir, inter->cam_ray.dir);

	ray.origin = rotated_origin; //pointeurs : verifier que je ne changes pas reellement les valeurs
	ray.dir = rotated_direction; */
/////////////////

	ray = inter->cam_ray;
	maths.x = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	maths.y = 2 * (ray.dir.x * (ray.origin.x - cylinder->pos.x) + 
		ray.dir.y * (ray.origin.y - cylinder->pos.y));
	maths.z = (ray.origin.x - cylinder->pos.x) * (ray.origin.x - cylinder->pos.x) + 
		(ray.origin.y - cylinder->pos.y) * (ray.origin.y - cylinder->pos.y) - 
		(cylinder->diameter / 2) * (cylinder->diameter / 2);

	return(maths);
}

/* Checks if camera_ray intersects with the side plane (if delta > 0)
 and if the intersection happens inside the cylinder's height */
static float	tube(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	float delta;
	float	t;
	float	t1;
	float	t2;
	float	z1;
	float	z2;

	t = FLT_MAX;

	maths = get_vec_abc(inter, cylinder);

	delta = maths.y * maths.y - 4 * maths.x * maths.z;

	if (delta >= 0) 
	{
		t1 = (-maths.y + sqrt(delta)) / (2 * maths.x);
		t2 = (-maths.y - sqrt(delta)) / (2 * maths.x);

		z1 = inter->cam_ray.origin.z + t1 * inter->cam_ray.dir.z;
		z2 = inter->cam_ray.origin.z + t2 * inter->cam_ray.dir.z;

//////////////////
/* 		t_vec transformed_origin = transform_ray_origin(inter->cam_ray.origin, cylinder->pos, cylinder->dir);
		t_vec transformed_direction = transform_ray_direction(inter->cam_ray.dir, cylinder->dir);

		z1 = transformed_origin.z + t1 * transformed_direction.z;
		z2 = transformed_origin.z + t2 * transformed_direction.z; */


/* 		t_vec rotated_origin = RotateByDir(cylinder->dir, cylinder->dir, vec_substract(inter->cam_ray.origin, cylinder->pos));
		t_vec rotated_direction = RotateByDir(cylinder->dir, cylinder->dir, inter->cam_ray.dir);

		z1 = rotated_origin.z + t1 * rotated_direction.z;
		z2 = rotated_origin.z + t2 * rotated_direction.z; */
//////////////////

		if (z1 >= cylinder->pos.z - cylinder->height / 2 && z1 <= cylinder->pos.z + cylinder->height / 2)
		{
			// printf("side 1\n");
			if (t1 > 0)
				t = t1;
		}
		if (z2 >= cylinder->pos.z - cylinder->height / 2 && z2 <= cylinder->pos.z + cylinder->height / 2)
		{
			// printf("side 2\n");
			if (t2 > 0 && t2 < t)
				t = t2;
		}
	}
	if (t != FLT_MAX)
		return (t);
	else
		return (0);
}

static float	closest_t(float t_top, float t_bottom, float t_side)
{
	float	t;
	
	t = FLT_MAX;
	if (t_top > 0 && t_top < t)
		t = t_top;
	if (t_bottom > 0 && t_bottom < t)
		t = t_bottom;
	if (t_side > 0 && t_side < t)
		t = t_side;
	if (t != FLT_MAX)
		return (t);
	else
		return (0);
}

/*We divide the cylinder into three objects : two planes and a tube.
We then check if the camera_ray intersects with any of these three objects*/
void intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
{
	float	t;
	float	t_top;
	float	t_bottom;
	float	t_side;
	
	t = 0.;
	t_top = upper_plane(inter, cylinder);
	t_bottom = bottom_plane(inter, cylinder);
	t_side = tube(inter, cylinder);
	// printf("height = %f\n", cylinder->height);
	// printf("hdiameter = %f\n", cylinder->diameter);
	
	t = closest_t(t_top, t_bottom, t_side);
	if (t > 0)
	{
		inter->obj = cylinder;
		inter->dist = t;
		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
		// inter->point = vec_add(RotateByDir((t_vec){0, 0, 1}, cylinder->dir, inter->point), cylinder->pos);
		if (t == t_side)
		{
			// printf("side\n");
			inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
			// inter->normal = RotateByDir(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t), cylinder->pos);
		}
		else if (t == t_top)
		{
			// printf("top\n");
			inter->normal = create_vec(0, 1, 0);
		}
		else if (t == t_bottom)
		{
			// printf("bottom\n");
			inter->normal = create_vec(0, -1, 0);
		}
	}
}
