/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/19 13:29:36 by amugnier         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data data;
	if (argc != 2)
	{
		printf("Error\nUsage ./miniRT <file.rt>\n");
		return (0);
	}
	if (parsing(argv[1], &data) == false)
		return (0);
	return (0);
}
