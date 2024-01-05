/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/05 18:14:52 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//effacer
#include <sys/wait.h>

/* void	init_img_black(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			img_pix_put(data, x, y, 65536); //black + 1 car sinon beugue
			x++;
		}
		y++;
	}
} */
void	ft_stop(t_data *data)
{
	t_objs	*tmp;
	while (data->scene.objs != NULL)
	{
		tmp = data->scene.objs->next;
		free(data->scene.objs);
		data->scene.objs = tmp;
	}
	data->scene.objs = NULL;
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(EXIT_SUCCESS);

}

int	esc_close(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_stop(data);
	return (0);
}

int	cross_close(t_data *data)
{
	ft_stop(data);
	return (0);
}

int	initialisation(t_data *data)
{
	(*data).win_ptr = NULL;
	(*data).mlx_ptr = mlx_init();
	if (!(*data).mlx_ptr)
	{
		printf("Error\nmlx_init() failed\n");
		return (EXIT_FAILURE);
	}
	(*data).win_ptr = mlx_new_window((*data).mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "mlx 42");
	if (!(*data).win_ptr)
	{
		printf("Error\nmlx_new_window() failed\n");
		return (EXIT_FAILURE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr  = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.width,
						&data->img.endian);
	// init_img_black(data); //pas sûre que ce soit nécessaire
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		printf("Error\nUsage ./miniRT <file.rt>\n");
		return (0);
	}
	if (parsing(argv[1], &data) == false)
		return (0); //need to change this return to 1 and continue test from action
	if (initialisation(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ray_generation(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	mlx_hook(data.win_ptr, 17, 1L<< 17, cross_close, &data);
	mlx_key_hook(data.win_ptr, esc_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
