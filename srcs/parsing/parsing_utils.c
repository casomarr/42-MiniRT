/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:54:32 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/08 15:55:03 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_nb_params(char **value, int nb_params, t_data *data)
{
	if (count_params(value) != nb_params)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters line : %d \n\x1B[0m", \
			data->scene.fname, data->scene.line, data->scene.line);
		return (false);
	}
	return (true);
}

bool	check_nb_cam(t_data *data)
{
	data->scene.nb_camera++;
	if (data->scene.nb_camera > 1)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Only one Camera is allowed\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	return (true);
}

bool	check_nb_ambiant(t_data *data)
{
	data->scene.nb_ambiant++;
	if (data->scene.nb_ambiant > 1)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Only one Ambiant is allowed\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	return (true);
}

bool	check_nb_light(t_data *data)
{
	data->scene.nb_light++;
	if (data->scene.nb_light > 1)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Only one Light is allowed\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	return (true);
}
