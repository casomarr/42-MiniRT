#include "minirt.h"

/*Calculates the norm of the angle of the ray from
camera to object and object to light source and then
calculates the norm of this angle.*/
void	get_norm(t_ray *ray)
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
}

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
void	generate_light_ray(t_data *data)
{
	t_objs *light;

	light = get_node(data->scene.objs, LIGHT);
	// data->light_ray.origin = light->position; //fait que la lumiere soit a l envers au niveau du brdf
	// data->light_ray.direction = vec_substract(data->closest_intersection_point, light->position);
	data->light_ray.origin = data->closest_intersection_point; //TEST
	data->light_ray.direction = vec_substract(light->position, data->closest_intersection_point); //TEST
	// data->light_ray.direction = create_vec(1.0, 0.0, 0.0); //TEST
	get_norm(&data->light_ray);
	normalize_direction_vector(&data->light_ray);
	data->direct_light = true;


	// float distance = vec_length(data->light_ray.direction);
	// data->light_intensity *= 1.0 / (distance * distance);
}

/*Generates each ray. They all have the same origin (the camera center)
but their direction changes (they reach a different pixel on the canevas
and continue in that direction into the scene)*/
void	generate_camera_ray(t_data *data)
{
	t_objs	*camera;
	t_vec	current_pixel;

	camera = get_node(data->scene.objs, CAMERA);
	if (camera == NULL)
	{
		ft_dprintf(2, "Error\nCrash getting camera node\n");
		return ;
	}
	data->ray.origin = camera->position;
	current_pixel = create_vec(data->x, data->y, 1);
	
	float aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	float fov_adjustment = tan((camera->fov / 2.0) * (PI / 180.0));
	float x = (2 * ((data->x + 0.5) / WIN_WIDTH) - 1) * fov_adjustment * aspect_ratio;
	float y = (/* 1 -  */2 * ((data->y + 0.5) / WIN_HEIGHT) - 1) * fov_adjustment;
	//calculs de rotation de la camera
	current_pixel = vec_add(data->ray.origin, create_vec(x, y, 1));
	
	data->ray.direction = vec_substract(current_pixel, data->ray.origin);
	get_norm(&data->ray);
	normalize_direction_vector(&data->ray);
}

/*Calculates each ray's direction.*/
void ray_generation(t_data *data)
{

	data->direct_light = true; //initialiser ici sinon qd light == NULL ou lightness == 0 elle n est pas initialisee donc conditional jump dans determine color
	data->y = 0;
	while (data->y < WIN_HEIGHT)
	{
		data->x = 0;
		while (data->x < WIN_WIDTH)
		{
			generate_camera_ray(data);
			if (intersection(data) == true)
			{
				if (get_node(data->scene.objs, LIGHT) != NULL && get_node(data->scene.objs, LIGHT)->lightness != 0.0)
				{
					generate_light_ray(data);
					check_intersection_light(data, &data->light_ray);
					//bouncing
				}
				img_pix_put(data, data->x, data->y, determine_pixel_color(data));
			}
/* 			else
				img_pix_put(data, data->x, data->y, GREEN); */
			data->x++;
		}
		data->y++;
	}
	printf("FINISHED\n");
}
