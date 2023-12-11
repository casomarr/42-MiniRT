/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/11 14:07:41 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <stdio.h>

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	printf("Hello World CARO!\n");
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (0);
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	if (!win_ptr)
		return (0);
	printf("%p\n", mlx_ptr);
	printf("%p\n", win_ptr);
	return (0);
}
