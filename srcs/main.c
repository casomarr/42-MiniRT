/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/11 14:07:41 by casomarr         ###   ########.fr       */
=======
/*   Updated: 2023/12/11 15:13:15 by amugnier         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
<<<<<<< HEAD
	void	*mlx_ptr;
	void	*win_ptr;

	printf("Hello World CARO!\n");
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
=======
	if (argc != 2)
	{
		printf("Error\nUsage ./miniRT <file.rt>\n");
>>>>>>> main
		return (0);
	}
	if (parsing(argv[1]) == false)
		return (0);
	return (0);
}
