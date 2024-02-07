/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:36:38 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/07 17:36:45 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// //TODO: dsl Antoine ne changeant le makefile ça me disait qu'il y avait
// deux main et deux ft_stop donc je les ai commentés

// void	ft_stop(t_data *data, short error)
// {
// 	t_objs	*tmp;
// 	while (data->scene.objs != NULL)
// 	{
// 		// if (data->scene.objs->next != NULL)
// 		tmp = data->scene.objs->next;
// 		// if (data->scene.objs)
// 		free(data->scene.objs);
// 		data->scene.objs = tmp;
// 	}
// 	data->scene.objs = NULL;
// 	if (error == STOP)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
// 		mlx_destroy_display(data->mlx_ptr);
// 		free(data->mlx_ptr);
// 	}
// 	exit(EXIT_SUCCESS);

// }

// int	main(int argc, char **argv)
// {
// 	t_data data;

// 	if (argc != 2)
// 	{
// 		printf("Error\nUsage ./miniRT <file.rt>\n");
// 		return (0);
// 	}
// 	if (parsing(argv[1], &data) == false)
// 	{
// 		ft_dprintf(2, "Error\nParsing failed\n");
// 		ft_stop(&data, PARSING_ERROR);
// 		return (0); //need to change this return to 1 and
//continue test from action
// 	}
// 	ft_stop(&data, STOP);
// 	return (0);
// }
