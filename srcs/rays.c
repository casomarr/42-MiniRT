/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:16:10 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/06 14:35:43 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Generates each ray. They all have the same origin (the camera center)
but their dir changes (they reach a different pixel on the canevas
and continue in that dir into the scene)*/
t_ray	compute_camera_ray(int x, int y, t_scene scene)
{
	t_ray	ray;
	t_objs	*camera;

	camera = scene.cam;
	ray.origin = camera->pos;
	float aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	float fov_adjustment = tan((camera->fov / 2.0) * (PI / 180.0));
	float xr = (2 * ((x + 0.5) / WIN_WIDTH) - 1) * fov_adjustment * aspect_ratio;
	float yr = (2 * ((y + 0.5) / WIN_HEIGHT) - 1) * fov_adjustment;
	ray.dir = vec_normalize(vec_add(vec_add(camera->dir, vec_multiply_float(scene.rdir, -xr)), vec_multiply_float(scene.udir, yr)));
	return (ray);
}

int	compute_pixel(int x, int y, t_data *data)
{
	t_ray 	ray;
	t_inter	inter;
	t_vec	v_rgb;
	t_vec	ambi_rgb;
	t_vec l_rgb;
	float ratio_camera_dist;
	t_inter interlight;

	ray = compute_camera_ray(x, y, data->scene); //TODO: verifier parsing erreur qd pas camera dans scene
	t_objs *camera = get_node(data->scene.objs, CAMERA);
	inter = closest_intersection(ray, data->scene.objs, MAX_DIST_CAMERA);
	if (inter.obj != NULL)
	{

		ratio_camera_dist =  1. - inter.dist / MAX_DIST_CAMERA;

		//tout ce qui suit dans ambient function
		t_color	color;
		t_objs	*ambient;
		t_vec	ambi_rgb;

		color = inter.obj->color;
		ambient = get_node(data->scene.objs, AMBIENT);
		ambi_rgb = (t_vec){color.bgra[2], color.bgra[1], color.bgra[0]};
		ambi_rgb = vec_min(ambi_rgb, (t_vec){ambient->color.bgra[2], ambient->color.bgra[1], ambient->color.bgra[0]});
		ambi_rgb = vec_multiply_float(ambi_rgb, ambient->lightness);
		if (data->render_ambiant == true)
			ambi_rgb = vec_multiply_float(ambi_rgb, ft_fabs(dot_product(ray.dir, inter.normal)));//a commenter pour enlever l'ombre avec la lumiere ambiante
		
		//tout ce qui suit dans light function
		t_inter interlight;
		t_objs	*light = get_node(data->scene.objs, LIGHT);
		t_vec l_rgb = vec_multiply_float((t_vec){color.bgra[2], color.bgra[1], color.bgra[0]}, light->lightness);
		t_vec point_to_light = vec_substract(light->pos, inter.point);
		float dist_light = get_norm(point_to_light);
		t_vec light_dir = vec_divide(point_to_light, dist_light); //changer calcul pour que ca colle avec nou calc dir camera
		interlight = closest_intersection((t_ray){inter.point, light_dir}, data->scene.objs, dist_light);
		l_rgb = vec_multiply_float(l_rgb, ft_fabs(dot_product(light_dir, inter.normal)));


		if (interlight.obj != NULL)
		 	v_rgb = ambi_rgb;
		else
			v_rgb = vec_max(l_rgb, ambi_rgb);
		return color_from_vec(v_rgb).full;
	}
	return (0);
}

/*Put object camera in structure scene for easier access later.
Normalizes the direction of all objects.
Sets the "right" and "up" vectors of the scene for camera_ray direction
calculation in compute_camera_ray : if the direction of the camera is
parallel to the up vector, we adjust the vector according to camera->dir
so that udir (=up direction) is orthogonal to camera->dir and world_up
and rdir (right direction) is orthogonal to rdir and camera->dir.*/
void	prepare_scene(t_data *data)
{
	t_objs *objs;
	t_vec	world_up = {0, 1, 0};
	t_vec	right;
	t_vec	up;

	objs = data->scene.objs; //on le remet au début
	while (objs)
	{
		if (objs->type == PLANE || objs->type == CAMERA || objs->type == CYLINDER)
			objs->dir = vec_normalize(objs->dir);
		objs = objs->next;
	}
	objs = get_node(data->scene.objs, CAMERA);
	data->scene.cam = objs;
	if (fabs(objs->dir.x) < 1e-6 && fabs(objs->dir.z) < 1e-6)
	{
		if (objs->dir.y > 0)
			world_up = (t_vec){0, 0, -1};
		else
			world_up = (t_vec){0, 0, 1};
	}
	data->scene.rdir = vec_normalize(vec_cross(objs->dir, world_up));
	data->scene.udir = vec_cross(data->scene.rdir, objs->dir);
}

/*Calculates each ray's dir.*/
void minirt(t_data *data)
{
	int x;
	int y;
	int	color;

	prepare_scene(data);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = compute_pixel(x, y, data);
			img_pix_put(data, x, y, color);
			x++;
		}
		y++;
	}
	// printf("FINISHED\n");
}
