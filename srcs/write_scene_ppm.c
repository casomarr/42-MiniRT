/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_scene_ppm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:19:57 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/29 19:22:56 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_scene_ppm(t_data *data)
{
	int			fd;
	int			x;
	int			y;
	t_color		color;
	float		xr;
	float		yr;
	int			sx = 500;
	int			sy = 500;

	xr = (float)(sx / WIN_WIDTH);
	yr = (float)(sy / WIN_HEIGHT);
	//rajouter les proportion à partir de WIN_WIDTH/2 et WIN_HEIGHT/2
	//Ctoupareil
	//ok aller je quitte, la je dois go cia cia des bisous =D

	fd = open("image.ppm", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nOpen failed\n");
		return ;
	}
	ft_dprintf(fd, "P3\n%d %d\n255\n", 800, 800);
	y = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < 800)
		{
			color.full = compute_pixel(x,y,data);
			img_pix_put(data, x, y, color.full);
			ft_dprintf(fd, "%d %d %d\n", color.bgra[2], color.bgra[1], color.bgra[0]);
			x++;
		}
		y--;
	}
	close(fd);
	printf("Image created\n");
}
