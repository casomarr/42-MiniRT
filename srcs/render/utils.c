/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:23:42 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/08 16:21:34 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the node we are looking for */
t_objs	*get_node(t_objs *objs, int type)
{
	t_objs	*current;

	current = objs;
	while (current)
	{
		if (current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	change_ambiant_render(int keycode, t_data *data)
{
	if (keycode == KEY_M)
	{
		if (data->render_ambiant == false)
			data->render_ambiant = true;
		else
			data->render_ambiant = false;
		minirt(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img.mlx_img, 0, 0);
	}
	if (keycode == KEY_R)
	{
		if (parsing(data->scene.fname, data) == false)
		{
			printf("Error\nParsing failed\n");
			ft_stop(data, PARSING_ERROR);
			return (1);
		}
		minirt(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img.mlx_img, 0, 0);
	}
	return (0);
}
