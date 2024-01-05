/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/05 16:11:33 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	initialisation(t_data *data)
// {
// 	(*data).win_ptr = NULL;
// 	(*data).mlx_ptr = mlx_init();
// 	if (!(*data).mlx_ptr)
// 	{
// 		printf("Error\nmlx_init() failed\n");
// 		return (EXIT_FAILURE);
// 	}
// 	(*data).win_ptr = mlx_new_window((*data).mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "mlx 42");
// 	if (!(*data).win_ptr)
// 	{
// 		printf("Error\nmlx_new_window() failed\n");
// 		return (EXIT_FAILURE);
// 	}
// 	data->img.mlx_img = NULL;
// 	return (EXIT_SUCCESS);
// }

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
	// mlx_clear_window(data->mlx_ptr, data->win_ptr); //a voir si on doit le mettre
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	esc_close(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_stop(data);
	return (0);
}

int	cross_close(t_data *data)
{
	(void)data;
	ft_stop(data);
	printf("coucou\n");
	return (0);
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
	{
		printf("Error\nParsing failed\n");
		return (0);
	}
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		printf("Error\nmlx_init() failed\n");
		return (EXIT_FAILURE);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "mlx 42");
	mlx_hook(data.win_ptr, 17, 1L << 17, cross_close, &data);
	mlx_key_hook(data.win_ptr, esc_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
