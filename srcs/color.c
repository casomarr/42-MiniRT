/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/02 18:18:37 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(unsigned char color, float light_intensity)
{
	// float	color;

	color = (float)color * light_intensity;
	if (color >= 255.0) //au cas ou on essayerait de rendre le blanc encore plus blanc
		return(255);
	else
		return((t_uint8)(color + 0.5));
}

/*In case of intersection between the ray leaving the camera and
an object of the scene, this function make the ray go from the
intersection to the light source.
- If the light source is attainable, we calculate the distance
betwen the light source and the object, and the BRDF.
- If the light source is not attainable, we calculate the shadows.
In both cases we get a light_intensity value that is then multiplied
by the color of the intersected object, which gives us the color
of the current pixel.*/
int	determine_pixel_color(t_data *data)
{
	int	light_intensity;
	t_rgb	color;

	color.full = data->front_object_color;

	// if (direct_light(data) == true)
	if (data->direct_light == true)
	{
		// printf("DIRECT LIGHT\n");
		// printf("object color = %d\n", data->front_object_color);
		// exit(1);
		
		light_intensity = distance_light_object(data) * brdf(data); //numero entre 0 et 1
		// light_intensity = 1; //test pour 2 sphères car light_intensity est négatif sinon
		//on s'en fout de color.argb[0] (= alpha)
		color.argb[1] = get_color(color.argb[1], light_intensity);
		color.argb[2] = get_color(color.argb[2], light_intensity);
		color.argb[3] = get_color(color.argb[3], light_intensity);
	}
	else
	{
		// printf("INDIRECT LIGHT\n");
		// printf("object color = %d\n", data->front_object_color);
		// exit(1);

		color.argb[1] = get_color(color.argb[1], shadows(data));
		color.argb[2] = get_color(color.argb[2], shadows(data));
		color.argb[3] = get_color(color.argb[3], shadows(data));
	}

	// printf("color = %d\n", color.full);
	// printf("light intensity = %d\n", light_intensity);

	return (color.full);
}

// void	determine_pixel(t_data *data)
// {
// 	//fonction patou
//
// 	int tmp;
// 	int x;
// 	int y;

// 	tmp = ray_location.x + WIN_WIDTH * ray_location.y;
// 	x = tmp % WIN_WIDTH;
// 	y = tmp / WIN_WIDTH;

// 	while (tmp < WIN_WIDTH * WIN_HEIGHT)
// 	{
// 		tmp++;
// 		x = tmp % WIN_WIDTH;
// 		y = tmp / WIN_WIDTH;
// 		printf("on est sur le pixel %d:%d\n", x, y);
// 	}
// }