/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:46:23 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/14 17:03:54 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*To add a new node when creating the cmd_list.*/
t_obj	*lstnew(int object)
{
	t_obj	*new;

	new = ft_calloc(1, sizeof(t_obj));
	if (!new)
		return (NULL);
	new->type = object;
	new->nb = 0;
    //etc
	new->next = NULL;
	return (new);
}

void	newimg_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->width + x * (img->bpp / 8)); //magie voudou demander a patou
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0) //big endian
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else //litle endian
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
	img->tab[y][x] = color;
	//printf("color : %d\n", color);
}