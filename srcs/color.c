/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/18 20:11:25 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Checks if the light source is reachable by a straight
line from the point of intersection. If not, it means the
current pixel is in the shadow.*/
bool	direct_light(t_data *data)
{
	////
}

/*In case of intersection between the ray leaving the camera and
an object of the scene, this function make the ray go from the
intersection to the light source.
- If the light source is attainable, we calculate the norm (thanks
to the angle of the ray), the distance betwen the light source and
the object, and the direction of the ray entering and leaving the object.
- If the light source is not attainable, we calculate the shadows.
In both cases we get a light_intensity value that is then multiplied
by the color of the intersected object, which gives us the color
of the current pixel.*/
int	determine_pixel_color(t_data *data)
{
	int	light_intensity;
	int	color;
	
	light_intensity = 0; //ou 1 vu que multiplication en bas?
	color = 0;
	if (direct_light(data) == true)
	{
		light_intensity = distance_light_object(data) * brdf(data);
		color = data->current_pixel_color * light_intensity
	}
	else
	{
		color = data->current_pixel_color * shadows(data);
	}
	return (color);
}

// void	determine_pixel(t_data *data)
// {
// 	/*fonction patou pour determine le pixel mais je crois
// 	que pas besoin et que je peux reutiliser mon x, y dans data->x
// 	et data->y qui correspond au ray generation.*/
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

// 	if (//?????)
// 		*intersection = true; */
// }