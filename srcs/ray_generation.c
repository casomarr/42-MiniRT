/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:53:12 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/13 19:12:47 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_init(t_data *data) //ou direct envoyer que le ray pour que lignes plus courtes pour norme
{
	//Camera
	float	focal_length = 1.0;
	float	viewport_height = 2.0;
	float	viewport_width = viewport_height * (data->img.width /data->img.height);
	
	//data->ray.camera_center = {0.0, 0.0, 0.0}; //le pixel au centre de WIN_HEIHT et WIN_WIDTH
	data->ray.camera_center.x = 0.0;
    data->ray.camera_center.y = 0.0;
    data->ray.camera_center.z = 0.0;
	
	//pour les 2 lignes suivantes : soit 1 soit viewport (commentes plus haut).
	data->ray.pixel_delta_w = 1 / WIN_WIDTH; //w pour width
	data->ray.pixel_delta_h = 1 / WIN_HEIGHT; //h pour hight

	//calcul localisation du pixel en haut a gauche
	t_vec	upper_left = {0.0, 0.0, focal_length};
	
	//t_vec	viewport_pixel_00 = vec_substract(camera_center, upper_left);
	// t_vec	viewport_pixel_00 = vec_substract(viewport_pixel_00, viewport_width);
	// t_vec	viewport_pixel_00 = vec_substract(viewport_pixel_00, viewport_height);
	t_vec	viewport_pixel_00 = vec_substract(data->ray.camera_center, upper_left);
    viewport_pixel_00.x -= viewport_width;
    viewport_pixel_00.y -= viewport_height;
	
	t_vec	vector_pixel_delta = {0.5f * (data->ray.pixel_delta_w + data->ray.pixel_delta_h), \
	0.5f * (data->ray.pixel_delta_w + data->ray.pixel_delta_h), 0.0f}; //c'est bien pour l'offset qu on le multiplie par 0.5?
	data->ray.pixel_00_location = vec_add(viewport_pixel_00, vector_pixel_delta);
	ray_generation (data); //ou direct envoyer que le ray pour que lignes plus courtes pour norme
}

void	ray_generation(t_data *data)
{
	int	i;
	int	j;
	t_vec	center_pixel;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			//center_pixel = vec_add(data->ray.pixel_00_location, (i * data->ray.pixel_delta_h));
			center_pixel.y = data->ray.pixel_00_location.y + (i * data->ray.pixel_delta_h);
			//center_pixel = vec_add(center_pixel, (j * data->ray.pixel_delta_w));
			center_pixel.x = center_pixel.x + (j * data->ray.pixel_delta_w);
			data->ray.direction = vec_substract(center_pixel, data->ray.camera_center);
			//determine if intersection and if yes determine color.
			if (intersection(data, j, i) == true)
			{
				//determine color
				//put color to window or to new layer?
			}
			j++;
		}
		i++;
	}
}
