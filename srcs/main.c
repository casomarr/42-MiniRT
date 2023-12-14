/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/14 15:09:59 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	initialisation(t_data *data)
{
	(*data).mlx_ptr = NULL;
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
	if (parsing(argv[1]) == false)
		return (0);
	if (initialisation(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	render(&data);
	//ray_init(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
