#include "minirt.h"

/*Calculates the norm of the angle of the ray from
camera to object and object to light source and then
calculates the norm of this angle.*/
/* void	get_norm(t_ray *ray)
{
//get_norm() ne marche que pour t_ray -->le changer pour eviter get_norm2()
	ray->norm = sqrtf(ray->direction.x * ray->direction.x + \
				ray->direction.y * ray->direction.y + \
				ray->direction.z * ray->direction.z);
}

void	normalize_direction_vector(t_ray *ray)
{
	if (ray->norm > 0)
	{
		ray->direction.x /= ray->norm;
		ray->direction.y /= ray->norm;
		ray->direction.z /= ray->norm;
	}
	else
	{
		ray->direction.x = 0.0f;
		ray->direction.y = 0.0f;
		ray->direction.z = 0.0f;
	}
} */

//part du point d'intersection vers la light
/* void	generate_light_ray(t_data *data)
{
	t_objs *light;

	light = get_node(data->scene.objs, LIGHT);
	data->light_ray.origin = data->closest_intersection_point;
	data->light_ray.direction = vec_substract(light->position, data->closest_intersection_point);
	get_norm(&data->light_ray);
	normalize_direction_vector(&data->light_ray);
	data->direct_light = true;
} */

float vec_length(t_vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//part de la light ers le point d'intersection
/* void	generate_light_ray(t_data *data)
{
	t_objs *light;

	light = get_node(data->scene.objs, LIGHT);
	// data->light_ray.origin = light->position; //fait que la lumiere soit a l envers au niveau du brdf
	// data->light_ray.direction = vec_substract(data->closest_intersection_point, light->position);
	data->light_ray.origin = data->closest_intersection_point; //TEST
	data->light_ray.direction = vec_substract(light->position, data->closest_intersection_point); //TEST
	// data->light_ray.direction = create_vec(1.0, 0.0, 0.0); //TEST
	// get_norm(&data->light_ray);
	// normalize_direction_vector(&data->light_ray);
	data->direct_light = true;


	// float distance = vec_length(data->light_ray.direction);
	// data->light_intensity *= 1.0 / (distance * distance);
} */

/*Generates each ray. They all have the same origin (the camera center)
but their direction changes (they reach a different pixel on the canevas
and continue in that direction into the scene)*/
t_ray	compute_screen_ray(int x, int y, t_objs *camera)
{
	t_ray	ray;

	ray.origin = camera->position;
	float aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	float fov_adjustment = tan((camera->fov / 2.0) * (PI / 180.0));
	float xr = (2 * ((x + 0.5) / WIN_WIDTH) - 1) * fov_adjustment * aspect_ratio;
	float yr = (/* 1 -  */2 * ((y + 0.5) / WIN_HEIGHT) - 1) * fov_adjustment;
	//calculs de rotation de la camera
	ray.dir = normalize_vec(create_vec(xr, yr, 1));
	return (ray);
}

t_rgb	from_color(t_uint8 r, t_uint8 g, t_uint8 b)
{
	t_rgb	rgb;

	rgb.full = 0;
	rgb.argb[0] = b;
	rgb.argb[1] = g;
	rgb.argb[2] = r;
	return (rgb);
}

int	compute_pixel(int x, int y, t_data *data)
{
	t_ray ray;
	t_inter	inter;
	t_vec	v_rgb;
	t_rgb	color;

	ray = compute_screen_ray(x, y, get_node(data->scene.objs, CAMERA)); //TODO: verifier parsing erreur qd pas camera dans scene
	inter = closest_intersection(ray, data->scene.objs);
	if (inter.obj != NULL)
	{
		color = inter.obj->color;
		v_rgb = (t_vec){color.argb[0] / 255., color.argb[1] / 255., color.argb[2] / 255.};
		v_rgb = vec_multiply_float(v_rgb, ft_fabs(dot_product(ray.dir, inter.normal)) * 255.);

		color = from_color(v_rgb.x, v_rgb.y, v_rgb.z);
		return color.full;
		return (inter.obj->color.full);
		/* if (get_node(data->scene.objs, LIGHT) != NULL && get_node(data->scene.objs, LIGHT)->lightness != 0.0)
		{
//			(t_ray){(t_vec){0.,0.,0.}, (t_vec){0.,0.,0.}}
			generate_light_ray(data);
			check_intersection_light(data, &data->light_ray);
			//bouncing
		} */
		//return (determine_pixel_color(data));
	}
	return (0);
}

/*Calculates each ray's direction.*/
void minirt(t_data *data)
{
	int x;
	int y;
	int	color;

	// data->direct_light = true; //initialiser ici sinon qd light == NULL ou lightness == 0 elle n est pas initialisee donc conditional jump dans determine color
	// data->y = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		// data->x = 0;
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = compute_pixel(x, y, data);
			//ray = compute_ray(x, y, data->camera);
			//ce dont t'as besoin = f(datas,x,y)
			/* compute_ray(data);
			if (intersection(data,x , y) == true)
			{
				if (get_node(data->scene.objs, LIGHT) != NULL && get_node(data->scene.objs, LIGHT)->lightness != 0.0)
				{
					generate_light_ray(data);
					check_intersection_light(data, &data->light_ray);
					//bouncing
				}
				img_pix_put(data, data->x, data->y, determine_pixel_color(data));
			} */
/* 			else
				img_pix_put(data, data->x, data->y, GREEN); */
			// data->x++;
			//img_pix_put(data, data->x, data->y, determine_pixel_color(data));
			img_pix_put(data, x, y, color);
			x++;
		}
		// data->y++;
		y++;
	}
	printf("FINISHED\n");
}
