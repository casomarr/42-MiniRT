/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/18 12:26:52 by casomarr         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

void	obj_init_pour_test(t_data *data)
{
	data->obj = *lstnew(SPHERE);
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
	obj_init_pour_test(&data);
	//render(&data);
	ray_init(&data);
	ray_generation(&data); //gives ray direction
	if (intersection(&data) == true) //ray_camera_object
	{
		determine_pixel_color(&data); //dedans : calculate_norm(&data); //ray_object_light
		add_pixel_to_img(&data); //first time : create image
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0); //if not intersection : pixel stays black (by default)
	mlx_loop(data.mlx_ptr);
	return (0);
}
