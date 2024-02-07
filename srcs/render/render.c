/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:21:40 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/07 16:50:48 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Changes the image's pixel color to the one sent in parameters.
The first condition is for big endian working graphic libraries
(where mos significant byte is the leftmost bit) and the second
condition is for little endian systems (where the least significant
byte is the leftmost bit) */
void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = data->img.bpp - 8;
	pixel = data->img.addr + ((WIN_HEIGHT - 1 - y) \
	* data->img.width + x * (data->img.bpp / 8));
	while (i >= 0)
	{
		if (data->img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
