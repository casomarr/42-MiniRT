/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/18 12:24:50 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* int determine_color(t_data *data, int x, int y)
{
	int	tmp;
	int	color;
	
	tmp = x + WIN_WIDTH * y;
	x = tmp % WIN_WIDTH;
	y = tmp / WIN_WIDTH;

	printf("on est sur le pixel %d:%d\n", x, y);
	data->ray.color = WHITE;
	color = data->ray.color * data->img.tab[x][y];

	return (color);
} */

int	determine_pixel_color(t_data *data)
{
	int	light_intensity;
	int	color;
	
	light_intensity = 0;
	color = 0; //c'est quelle couleur 0?
	if (direct_light(data) == true) //if we can touch the light from intersection ray/object point
	{
		calculate_norm(data); /*calculates angle from intersection
		of ray and object to light source and then calculates the
		norm of this angle*/
		light_intensity = distance_light_object(data) * brdf(data);
		//distance_light_object = inverse square law
		//pas sure qu il faille multiplier distance par BRDF
		color = data->current_pixel_color * light_intensity
		
	}
	else
	{
		color = data->current_pixel_color * shadows(data);
		//pas sure pour a multiplication
	}
	return (color);
}