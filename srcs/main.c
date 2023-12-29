/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/29 16:34:56 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	data->img.mlx_img = NULL;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data data;
	// int	color;
	
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
	// color = 0;
	if (intersection(&data) == true)
	{
		//determine_pixel(); //necessaire?
		printf ("INTERSECTION FOUND\n");
		exit (1); //test
		//color = determine_pixel_color(&data);
		//add_pixel_to_img(&data, color);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0); //if not intersection : pixel stays black (by default)
	mlx_loop(data.mlx_ptr);
	return (0);
}
