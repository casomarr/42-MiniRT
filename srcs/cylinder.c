/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:09:52 by octonaute         #+#    #+#             */
/*   Updated: 2024/01/18 15:49:43 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec vec_rotate(t_vec vector, t_vec axis) {
	t_vec result;

	float cos_theta = cosf(axis.x);
	float sin_theta = sinf(axis.x);

	float x_rot = vector.x;
	float y_rot = cos_theta * vector.y - sin_theta * vector.z;
	float z_rot = sin_theta * vector.y + cos_theta * vector.z;

	result.x = x_rot;
	result.y = cosf(axis.y) * y_rot + sinf(axis.y) * z_rot;
	result.z = -sinf(axis.y) * y_rot + cosf(axis.y) * z_rot;

	return result;
}

t_vec vec_invert(t_vec vector) {
	t_vec result;

	result.x = -vector.x;
	result.y = -vector.y;
	result.z = -vector.z;

	return result;
}

void check_intersection_cylinder(t_objs *cylinder, t_ray *ray)
{
	t_vec calc;

	// Transform ray into cylinder's local space
	t_vec local_origin = vec_substract(ray->origin, cylinder->position);
	t_vec local_direction = vec_rotate(ray->direction, vec_invert(cylinder->direction));

	// Cylinder axis is y-axis
	calc.x = powf(local_direction.x, 2) + powf(local_direction.z, 2);
	calc.y = 2 * (local_origin.x * local_direction.x + local_origin.z * local_direction.z);
	calc.z = powf(local_origin.x, 2) + powf(local_origin.z, 2) - powf(cylinder->diameter / 2, 2);

	// Solve quadratic equation for t
	ray->discriminant = calc.y * calc.y - 4 * calc.x * calc.z;

	if (ray->discriminant < 0)
		return;  // No intersection

	float t1 = (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x);
	float t2 = (-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x);

	if ((t1 > 0 && t2 > 0 && t1 < t2) || (t1 > 0 && t2 < 0))
		ray->t = (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x);
	else if (t2 > 0)
		ray->t = (-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x);
}

void intersection_point_cylinder(bool *intersection, t_data *data, t_objs *cylinder, t_ray *camera_ray)
{
	// Check if intersection points are within cylinder height
	float y = camera_ray->origin.y + camera_ray->t * dot_product(camera_ray->direction, cylinder->direction);

	//printf("y = %f, cylinder height: %f\n", y, cylinder->height);
	if (camera_ray->discriminant >= 0 && y >= 0 && y <= cylinder->height)
	{
		// printf("cylinder intersection found\n");
		*intersection = true;  // Intersection within cylinder height
		t_vec intersection_point_local = vec_add(camera_ray->origin, vec_multiply_float(camera_ray->direction, camera_ray->t));
		// if ((powf(intersection_point_local.x, 2) + powf(intersection_point_local.z, 2)) <= powf(cylinder->diameter / 2, 2))
		// {
			//printf("cylinder intersection found\n");
			// Transform intersection point back to world space
			t_vec intersection_point_world = vec_add(vec_rotate(intersection_point_local, cylinder->direction), cylinder->position);
			if (camera_ray->t > 0 && camera_ray->t < data->z_index) //camera_ray->t > 0 car sinon derriere camera
			{
				data->z_index = camera_ray->t;
				data->closest_intersection_point = intersection_point_world;
				data->closest_object = *cylinder;
			}
		// }
	}
}
