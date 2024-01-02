/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:53:12 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/18 20:14:29 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	aspect_ratio = 16.0 / 9.0; //ajoute pour ray_generation
// data->img.height = data->img.width / aspect_ratio; //ajoute pour ray_generation

/*Initializes the rays*/
void	ray_init(t_data *data) //ou direct envoyer que le ray pour que lignes plus courtes pour norme
{
	t_ray	*ray;

	ray = data->ray;
	
	//Camera
	float	focal_length = 1.0;
	float	viewport_height = 2.0;
	float	viewport_width = viewport_height * (data->img.width /data->img.height);

	//on set l'origine du rayon ( = le centre de la camera)
	ray.origin = data->camera.position;
	
	//on calcule l'espace entre chaque pixel (a quel point les rayons seront proches)
	ray.pixel_delta_w = 1 / WIN_WIDTH; //soit 1 soit viewport
	ray.pixel_delta_h = 1 / WIN_HEIGHT; //soit 1 soit viewport

	//localisation du pixel en haut a gauche
	t_vec	current_pixel = {data->x, data->y, focal_length};
	
	//zone (=viewport) correspondant au pixel en haut a gauche
	t_vec	viewport_current_pixel = vecSubstract(ray.origin, current_pixel);
    viewport_current_pixel.x -= viewport_width;
    viewport_current_pixel.y -= viewport_height;

	//viewport pour chaque pixel
	t_vec	vector_pixel_delta = {0.5f * (ray.pixel_delta_w + ray.pixel_delta_h), \
	0.5f * (ray.pixel_delta_w + ray.pixel_delta_h), 0.0f}; //c'est bien pour l'offset qu on le multiplie par 0.5?

	//localisation du premier viewport en haut a gauche
	ray.current_pixel_location = vecAdd(viewport_current_pixel, vector_pixel_delta);

	//ray.enter_direction = vecAdd(ray.origin, ray.pixel_00_location, ??);

	// Calculate the direction vector from camera to pixel
	ray.enter_direction = vecSubstract(ray.pixel_00_location, ray.origin);

	// Normalize the direction vector
	get_norm(data);

	// Normalisation de la norme
	ray.enter_direction.x /= ray.norm;
	ray.enter_direction.y /= ray.norm;
	ray.enter_direction.z /= ray.norm;
}

/*Calculates the norm of the angle of the ray from
camera to object and object to light source and then
calculates the norm of this angle.*/
void	get_norm(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	ray.norm = sqrt(ray.enter_direction.x * ray.enter_direction.x + \
				ray.enter_direction.y * ray.enter_direction.y + \
				ray.enter_direction.z * ray.enter_direction.z);
}

/*Calculates each ray's direction.*/
void	ray_generation(t_data *data)
{
	t_vec	center_pixel;

	while (data->y < WIN_HEIGHT)
	{
		data->x = 0;
		while (data->x < WIN_WIDTH)
		{
			ray_init(data);
			data->x++;
		}
		data->y++;
	}
}
