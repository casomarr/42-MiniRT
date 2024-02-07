/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_compile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:30:11 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/07 16:33:07 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_compile.h"

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;

	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (0);
	}
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		printf("Error\nmlx_init() failed\n");
		return (0);
	}
	printf("%p\n", mlx_ptr);
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	if (!win_ptr)
	{
		printf("Error\nmlx_new_window() failed\n");
		return (0);
	}
	printf("%p\n", win_ptr);
	printf("Hello World! -> %s\n", argv[1]);
}
