/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/29 19:56:06 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_img_black(t_data *data)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			add_pixel_to_img(data, 65536); //black + 1 car sinon beugue
			x++;
		}
		y++;
	}
	//caro : TEST EN COURS. EFFACER LES DEUX LIGNES CI-DESSOUS LORSQUE SEGFAULT RÉGLÉE
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	exit(1);
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
	data->img.mlx_img = NULL;
	init_img_black(data); //pas sûre que ce soit nécessaire
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
	/* if (initialisation(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ray_generation(&data);
	color = 0;
	if (intersection(&data) == true)
	{
		//determine_pixel(); //necessaire?
		// printf ("INTERSECTION FOUND\n");
		// exit (1); //test
		color = determine_pixel_color(&data);
		add_pixel_to_img(&data, color);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	mlx_loop(data.mlx_ptr); */
	return (0);
}
