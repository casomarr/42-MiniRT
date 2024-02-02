/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:21:40 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/01 15:17:28 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = data->img.bpp - 8;

	pixel = data->img.addr + ((WIN_HEIGHT - 1 - y) * data->img.width + x * (data->img.bpp / 8)); //magie voudou demander a patou
	while (i >= 0)
	{
		if (data->img.endian != 0) /* big endian, MSB is the leftmost bit */
			*pixel++ = (color >> i) & 0xFF;
		else /* little endian, LSB is the leftmost bit */
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
