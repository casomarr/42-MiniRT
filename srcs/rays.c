#include "minirt.h"

/*Calculates the norm of the angle of the ray from
camera to object and object to light source and then
calculates the norm of this angle.*/
/* void	get_norm(t_ray *ray)
{
//get_norm() ne marche que pour t_ray -->le changer pour eviter get_norm2()
	ray->norm = sqrtf(ray->dir.x * ray->dir.x + \
				ray->dir.y * ray->dir.y + \
				ray->dir.z * ray->dir.z);
}

void	normalize_direction_vector(t_ray *ray)
{
	if (ray->norm > 0)
	{
		ray->dir.x /= ray->norm;
		ray->dir.y /= ray->norm;
		ray->dir.z /= ray->norm;
	}
	else
	{
		ray->dir.x = 0.0f;
		ray->dir.y = 0.0f;
		ray->dir.z = 0.0f;
	}
} */

//part du point d'intersection vers la light
/* void	generate_light_ray(t_data *data)
{
	t_objs *light;

	light = get_node(data->scene.objs, LIGHT);
	data->light_ray.origin = data->closest_intersection_point;
	data->light_ray.dir = vec_substract(light->pos, data->closest_intersection_point);
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
	// data->light_ray.origin = light->pos; //fait que la lumiere soit a l envers au niveau du brdf
	// data->light_ray.dir = vec_substract(data->closest_intersection_point, light->pos);
	data->light_ray.origin = data->closest_intersection_point; //TEST
	data->light_ray.dir = vec_substract(light->pos, data->closest_intersection_point); //TEST
	// data->light_ray.dir = create_vec(1.0, 0.0, 0.0); //TEST
	// get_norm(&data->light_ray);
	// normalize_direction_vector(&data->light_ray);
	data->direct_light = true;


	// float distance = vec_length(data->light_ray.dir);
	// data->light_intensity *= 1.0 / (distance * distance);
} */

/*Generates each ray. They all have the same origin (the camera center)
but their dir changes (they reach a different pixel on the canevas
and continue in that dir into the scene)*/
t_ray	compute_screen_ray(int x, int y, t_scene scene)
{

//AVANT TUTO
	t_ray    ray;
	t_objs *camera;

	camera = scene.cam;
	ray.origin = camera->pos;
	float aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	float fov_adjustment = tan((camera->fov / 2.0) * (PI / 180.0));
	float xr = (2 * ((x + 0.5) / WIN_WIDTH) - 1) * fov_adjustment * aspect_ratio;
	float yr = (/* 1 -  */2 * ((y + 0.5) / WIN_HEIGHT) - 1) * fov_adjustment;

	//calculs de rotation de la camera
	// ray.dir = vec_normalize(create_vec(xr, yr, 1));
	ray.dir = vec_normalize(vec_add(vec_add(camera->dir, vec_multiply_float(scene.rdir, xr)), vec_multiply_float(scene.udir, yr)));


/* 	t_ray    ray;

	ray.origin = scene.cam->pos;
	// t_vec	curr_pixel = vec_add_float(scene.first_pixel, (x * scene.pixel_delta_u + y * scene.pixel_delta_v));
	t_vec	curr_pixel = vec_add(vec_add(scene.first_pixel, vec_multiply_float(scene.pixel_delta_u, x)), vec_multiply_float(scene.pixel_delta_v, y));
	//t_vec	curr_pixel = create_vec(scene.first_pixel.x + x, scene.first_pixel.y + y, 1.0);
	//t_vec	curr_pixel = create_vec(x, y, 1);
	// ray.dir = vec_normalize(vec_substract(curr_pixel, ray.origin));
	ray.dir = vec_substract(curr_pixel, ray.origin); //ca normalize */

	
	// printf("scene.first_pixel = %f,%f,%f\n", scene.first_pixel.x, scene.first_pixel.y, scene.first_pixel.z);
	// printf("x = %d, y = %d\n", x, y);
	// printf("current_pixel = %f,%f,%f\n", curr_pixel.x, curr_pixel.y, curr_pixel.z);
	// if (x == 1)
	// 	exit(1);

	
	return (ray);
}



t_color	color_from_rgb(t_uint8 r, t_uint8 g, t_uint8 b)
{
	t_color	rgb;

	rgb.full = 0;
	rgb.bgra[0] = b;
	rgb.bgra[1] = g;
	rgb.bgra[2] = r;
	return (rgb);
}
t_color	color_from_vec(t_vec v)
{
	return (color_from_rgb(v.x, v.y, v.z));
}

t_vec	vec_max(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret = v1;
	if (v1.x < v2.x)
		ret.x = v2.x;
	if (v1.y < v2.y)
		ret.y = v2.y;
	if (v1.z < v2.z)
		ret.z = v2.z;
	return (ret);
}

t_vec	vec_min(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret = v1;
	if (v1.x > v2.x)
		ret.x = v2.x;
	if (v1.y > v2.y)
		ret.y = v2.y;
	if (v1.z > v2.z)
		ret.z = v2.z;
	return (ret);
}
// float	clamp(float value, float min, float max)
// {
// 	if (value < min)
// 		return (min); //pour éviter noir --> ambient light
// 	if (value > max)
// 		return(max);
// 	return (value);
// }

t_vec	vec_clamp(t_vec v, float min, float max)
{
	return ((t_vec){clamp(v.x, min, max),clamp(v.y, min, max),clamp(v.z, min, max)});
}

t_vec	vec_product(t_vec a, t_vec b)
{
	t_vec ret = (t_vec){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
	if (ret.x == -0.)
		ret.x = 0;
	if (ret.y == -0.)
		ret.y = 0;
	if (ret.z == -0.)
		ret.z = 0;
	return (ret);
}

int	compute_pixel(int x, int y, t_data *data)
{
	t_ray 	ray;
	t_inter	inter;
	t_color	color;
	t_vec	v_rgb;

	ray = compute_screen_ray(x, y, data->scene); //TODO: verifier parsing erreur qd pas camera dans scene
	t_objs *camera = get_node(data->scene.objs, CAMERA);
	inter = closest_intersection(ray, data->scene.objs, MAX_DIST_CAMERA);
	if (inter.obj != NULL)
	{
		// if (inter.obj->type == SPHERE)
		// 	return (color_from_rgb(255,0,0).full);
		// if (inter.obj->type == PLANE)
		// 	return (color_from_rgb(0,255,0).full);


//bug america : odre de calul des couleurs
		color = inter.obj->color;
		float ratio_camera_dist =  1. - inter.dist / MAX_DIST_CAMERA;
		float	ambiratio = get_node(data->scene.objs, AMBIENT)->lightness;
		t_color ambicolor = get_node(data->scene.objs, AMBIENT)->color;
		t_vec	ambi_rgb;
		ambi_rgb = (t_vec){color.bgra[2], color.bgra[1], color.bgra[0]};
		ambi_rgb = vec_min(ambi_rgb, (t_vec){ambicolor.bgra[2], ambicolor.bgra[1], ambicolor.bgra[0]});
		ambi_rgb = vec_multiply_float(ambi_rgb, ambiratio);
//		v_rgb = vec_multiply_float(v_rgb, ft_fabs(dot_product(data->scene.cam->dir, inter.normal)));
		// ambi_rgb = vec_multiply_float(ambi_rgb, ft_fabs(dot_product(ray.dir, inter.normal)));//a commenter pour enlever l'ombre avec la lumiere ambiante
		t_inter interlight;
		t_objs	*light = get_node(data->scene.objs, LIGHT);
		t_vec l_rgb = vec_multiply_float((t_vec){color.bgra[2], color.bgra[1], color.bgra[0]}, light->lightness);
		t_vec point_to_light = vec_substract(light->pos, inter.point);
		float dist_light = get_norm(point_to_light);
		t_vec light_dir = vec_div_float(point_to_light, dist_light); //changer calcul pour que ca colle avec nou calc dir camera
		interlight = closest_intersection((t_ray){inter.point, light_dir}, data->scene.objs, dist_light);
		l_rgb = vec_multiply_float(l_rgb, ft_fabs(dot_product(light_dir, inter.normal)));

		if (interlight.obj != NULL)
		 	v_rgb = ambi_rgb;
		else
			v_rgb = vec_max(l_rgb, ambi_rgb);
		return color_from_vec(v_rgb).full;

		
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

void	prepare_scene(t_data *data)
{
	t_objs *objs;

	objs = get_node(data->scene.objs, CAMERA);
	data->scene.cam = objs;
	//TODO: bug qd dir camera y = -1 ou 1 et z = 0
	//fabs dir if y == 1 ou -1 et z = 0 alors changer udir et rdir

	//changements en cours
	data->scene.rdir = vec_product((t_vec){0.,1.,0.}, objs->dir);
	data->scene.udir = vec_product(objs->dir, data->scene.rdir);

	objs = data->scene.objs;
	while (objs)
	{
		if (objs->type == PLANE || objs->type == CAMERA || objs->type == CYLINDER)
			objs->dir = vec_normalize(objs->dir);
		objs = objs->next;
	}



//calculs preliminaires pourray_generation
// 	t_ray	ray;

// 	float	ratio = WIN_HEIGHT / WIN_WIDTH;
// 	float	viewport_height = (float)WIN_HEIGHT * ratio;
// 	float	viewport_width = (float)WIN_WIDTH * ratio;

// /* 	float	aspect_ratio = 16.0 / 9.0;
// 	float	img_width = 400;
// 	float	img_height = img_width / aspect_ratio;
// 	if (img_height < 1)
// 		img_height = 1;
//     float	viewport_height = 2.0; // Set to a fixed value
//     float	viewport_width = viewport_height * (img_width / img_height); */



// 	float	focal_length = 1.0;
// 	t_vec	viewport_u = create_vec(viewport_width, 0.0, 0.0);
// 	t_vec	viewport_v = create_vec(0.0, -viewport_height, 0.0);

// 	// float	pixel_delta_u = vec_divide_float(viewport_u, WIN_WIDTH);
// 	// float	pixel_delta_v = vec_divide_float(viewport_v, WIN_HEIGHT);

// 	t_vec	pixel_delta_u = vec_div_float(viewport_u, WIN_WIDTH);
// 	t_vec	pixel_delta_v = vec_div_float(viewport_v, WIN_HEIGHT);
// /* 
// 	float	pixel_delta_u = vec_divide_float(viewport_u, img_width);
// 	float	pixel_delta_v = vec_divide_float(viewport_v, img_height); */



// 	t_vec	viewport_upper_left = vec_substract(vec_substract(data->scene.cam->pos, (t_vec){0., 0., focal_length}), vec_substract(vec_divide(viewport_u, 2.), vec_divide(viewport_v, 2.)));
// 	// t_vec	pixel00_loc = vec_add_float(viewport_upper_left, (pixel_delta_u + pixel_delta_v) * 0.5f);
// 	t_vec	pixel00_loc = vec_add(viewport_upper_left, vec_multiply_float(vec_add(pixel_delta_u, pixel_delta_v), 0.5f));


// 	data->scene.first_pixel = pixel00_loc;
// 	data->scene.pixel_delta_u = pixel_delta_u;
// 	data->scene.pixel_delta_v = pixel_delta_v;
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
	printf("FINISHED\n");
}
