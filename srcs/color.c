/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/04 19:26:03 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(unsigned char color, float light_intensity)
{
	// float	color;

	// printf("color = %d\n", (int)color);
	// printf("light_intensity = %f\n", light_intensity);

/* 	color = (float)color * light_intensity;

	// printf("result = %f\n", (float)color);
	
	if (color >= 255.0) //au cas ou on essayerait de rendre le blanc encore plus blanc
		return(255);
	else
		return((t_uint8)(color + 0.5)); */

	float new_color = (float)color * light_intensity;
    new_color = roundf(new_color); // Rounds the float to the nearest integer

    if (new_color > 255.0)
        return 255;
    else if (new_color < 0.0)
        return 0;
    else
        return (int)new_color;
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
float	determine_pixel_color(t_data *data)
{

	// printf ("distance : %f\n", data->light_distance);

	
	float	light_intensity;
	t_rgb	color;

	color.full = data->front_object_color;

	// if (direct_light(data) == true)
	if (data->direct_light == false) //FALSE ET TRUE SONT INVERSÉS!!!
	{
		// printf("DIRECT LIGHT\n");
		// printf("object color = %d\n", data->front_object_color);
		// exit(1);
		
		light_intensity = /* distance_light_object(data) * */ brdf(data);
		// printf("light intensity = %f\n", light_intensity);
		
		// light_intensity = 1;
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
		// pause();

		// printf("color before shadowing = %d\n", color.full);
		
		light_intensity = /* shadows(data) *  */brdf(data);

		color.argb[1] = get_color(color.argb[1], light_intensity); //au lieu de shadows(data);
		color.argb[2] = get_color(color.argb[2], light_intensity);
		color.argb[3] = get_color(color.argb[3], light_intensity);

		// printf("color after shadowing = %d\n", color.full);
		
		// color.full = 13107400;
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