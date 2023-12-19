/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:21:40 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/18 15:54:44 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = data->img.bpp - 8;
	pixel = data->img.addr + (y * data->img.width + x * (data->img.bpp / 8)); //magie voudou demander a patou
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (data->img.endian != 0) //big endian
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else //litle endian
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	add_pixel_to_img(t_data *data, int color)
{
	if(data->img.mlx_img != NULL)
	{
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		data->img.addr  = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.width,
							&data->img.endian);
	}
	img_pix_put(data, data->x, data->y, color);
}