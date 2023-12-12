/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/12 18:23:16 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(/* int argc, char **argv */)
{
	/* if (argc != 2)
	{
		printf("Error\nUsage ./miniRT <file.rt>\n");
		return (0);
	}
	if (parsing(argv[1]) == false)
		return (0); */

	t_data data;
	
	data.mlx_ptr = NULL;
	data.win_ptr = NULL;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		printf("Error\nmlx_init() failed\n");
		return (0);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "mlx 42");
	if (!data.win_ptr)
	{
		printf("Error\nmlx_new_window() failed\n");
		return (0);
	}
	//render_tiles(&data); //test caro
	sphere_img(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
