/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/02 17:14:52 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(unsigned char color, float light_intensity)
{
	float new_color = (float)color * light_intensity;
	new_color = roundf(new_color); // Rounds the float to the nearest integer

	if (new_color > 255.0)
		return 255;
	else if (new_color < 0.0)
		return 0;
	else
		return (int)new_color; //return((t_uint8)(color + 0.5));
}

/*In case of intersection between the ray leaving the camera and
an object of the scene, this function makes the ray go from the
intersection to the light source.
- If the light source is attainable, we calculate the distance
betwen the light source and the object, and the BRDF.
- If the light source is not attainable, we calculate the shadows.
In both cases we get a light_intensity value that is then multiplied
by the color of the intersected object, which gives us the color
of the current pixel.*/
float	determine_pixel_color(t_data *data)
{
	float	light_intensity;
	t_color	color;

	color.full = data->closest_object.color.full;
	
	//temporaire pour afficher lumiere
	if (data->closest_object.type == LIGHT)
		return (color.full);

	if (data->direct_light == true) //points spheres : direct_light = false
		//light_intensity = brdf(data);
		light_intensity = 0.9;
	else
		light_intensity = get_node(data->scene.objs, AMBIENT)->lightness/*  * brdf(data) */;
	
	color.bgra[0] = get_color(color.bgra[0], light_intensity);
	color.bgra[1] = get_color(color.bgra[1], light_intensity);
	color.bgra[2] = get_color(color.bgra[2], light_intensity);
	return (color.full);
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