/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:44:16 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/31 19:14:18 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_stop(t_data *data, short error)
{
	t_objs	*tmp; //FIXME: data->scene.objs n existe pas si le fichier n existe pas flag necessaire a add
	while (data->scene.objs != NULL)
	{
		tmp = data->scene.objs->next;
		free(data->scene.objs);
		data->scene.objs = tmp;
	}
	data->scene.objs = NULL;
	if (error == STOP)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}

int	esc_close(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_stop(data, STOP);
	return (0);
}

int	cross_close(t_data *data)
{
	ft_stop(data, STOP);
	return (0);
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
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr  = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.width,
						&data->img.endian);
	data->scene.cam = get_node(data->scene.objs, CAMERA);
	return (EXIT_SUCCESS);
}

void	change_ambiant_render(int keycode, t_data *data)
{
	if (keycode == KEY_M)
	{
		if (data->render_ambiant== false)
			data->render_ambiant = true;
		else
			data->render_ambiant = false;
		// mlx_clear_window(data->mlx_ptr, data->win_ptr); //hmm voir pour optimiser
		minirt(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
}


int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		printf("Error\nUsage ./miniRT <file.rt>\n");
		return (0);
	}
	ft_bzero(&data, sizeof(t_data));
	if (parsing(argv[1], &data) == false)
	{
		printf("Error\nParsing failed\n");
		ft_stop(&data, PARSING_ERROR);
		return (0); //need to change this return to 1 and continue test from action
	}
	if (initialisation(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	minirt(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	// write_scene_ppm(&data);
	mlx_hook(data.win_ptr, 17, 1L<< 17, cross_close, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, change_ambiant_render, &data);
	mlx_key_hook(data.win_ptr, esc_close, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}



/* int main()
{
	// t_vec front = (t_vec){0, 0, 1};
	// t_vec right = (t_vec){1, 0, 0};
	// t_vec up = (t_vec){0, 1, 0};

	// t_vec	res;

	// res = vec_product(front, up); // = {-1, 0, 0}
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
	// res = vec_product(up, front); // = {1, 0, 0}
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
	// res = vec_product(front, right); // = {0, 1, 0}
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
	// res = vec_product(right, front); // = {0, -1, 0}
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
	// res = vec_product(right, up); // = {0, 0, 1} --> Ça donne bien front
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
	// res = vec_product(up, right); // = {0, 0, -1}
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);

	// res = vec_product(up, (t_vec){-0.5, 0, 0.5}); // = {0.5, -0, 0.5}
	// res = vec_product(res, vec_normalize((t_vec){dir.x, 0, dir.z})); // = {0.5, -0, 0.5}
	// printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);


	t_vec front = vec_normalize((t_vec){-0.5, 0.5, 0.5});
	t_vec up = (t_vec){0, 1, 0};
	t_vec	res;
	res = vec_product(up, vec_normalize((t_vec){front.x, 0, front.y})); // = {0.5, -0, 0.5}
	printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
	// 0.7, 0, 0.7
	res = vec_product(front, res);
	//res = vec_product(vec_normalize((t_vec){data->scene.cam->dir.x, 0, data->scene.cam->dir.z}), res); // = {0., 0.5, -0.}
	// 0.4, 0.8, -0.4
	printf("res = {%f, %f, %f}\n", res.x, res.y, res.z);
} */
