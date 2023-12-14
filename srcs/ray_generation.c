/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:53:12 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/14 15:32:38 by casomarr         ###   ########.fr       */
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
	
	//t_vec	viewport_pixel_00 = vecSubstract(camera_center, upper_left);
	// t_vec	viewport_pixel_00 = vecSubstract(viewport_pixel_00, viewport_width);
	// t_vec	viewport_pixel_00 = vecSubstract(viewport_pixel_00, viewport_height);
	t_vec	viewport_pixel_00 = vecSubstract(data->ray.camera_center, upper_left);
    viewport_pixel_00.x -= viewport_width;
    viewport_pixel_00.y -= viewport_height;
	
	t_vec	vector_pixel_delta = {0.5f * (data->ray.pixel_delta_w + data->ray.pixel_delta_h), \
	0.5f * (data->ray.pixel_delta_w + data->ray.pixel_delta_h), 0.0f}; //c'est bien pour l'offset qu on le multiplie par 0.5?
	data->ray.pixel_00_location = vecAdd(viewport_pixel_00, vector_pixel_delta);
	ray_generation (data); //ou direct envoyer que le ray pour que lignes plus courtes pour norme
}

void	ray_generation(t_data *data)
{
	int	y;
	int	x;
	t_vec	center_pixel;
	int	pixel_color;
	t_img	*new_img;

	y = 0;
	new_img = NULL;
	new_img->mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	new_img->addr  = mlx_get_data_addr(new_img->mlx_img, &new_img->bpp, &new_img->width,
								&new_img->endian);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			//center_pixel = vecAdd(data->ray.pixel_00_location, (i * data->ray.pixel_delta_h));
			center_pixel.y = data->ray.pixel_00_location.y + (y * data->ray.pixel_delta_h);
			//center_pixel = vecAdd(center_pixel, (j * data->ray.pixel_delta_w));
			center_pixel.x = center_pixel.x + (x * data->ray.pixel_delta_w);
			data->ray.direction = vecSubstract(center_pixel, data->ray.camera_center);
			//determine if intersection and if yes determine color.
			//if (intersection(data, j, i) == true)
			if (objects_iteration(data, x, y) == true)
			{
				printf("intersection = true\n");
				pixel_color = determine_color(data, x, y);
				newimg_pix_put(new_img, x, y, pixel_color);
				
			}
			else //juste pour test
				printf("intersection = false\n");
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, new_img->mlx_img, 0, 0);
}
