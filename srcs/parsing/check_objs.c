/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/08 16:03:35 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_isdigit_int(char *value, t_scene *scene)
{
	int	i;

	i = 0;
	if (ft_is_sign(value[i]))
		i++;
	if (check_ovf_int(value, scene, 11) == false)
		return (false);
	while (value[i] != '\0' && value[i] != '\n')
	{
		if (ft_isdigit(value[i]) == false)
		{
			ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
				"number is not an INT\n\x1B[0m", \
				scene->fname, scene->line);
			return (false);
		}
		i++;
	}
	if (value[i] == '\n')
		value[i] = '\0';
	return (true);
}

bool	check_isdigit_float(char *value)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (ft_is_sign(value[i]))
		i++;
	while (value[i] != '\0' && value[i] != '\n')
	{
		if (value[i] != '.')
		{
			if (ft_isdigit(value[i]) == false)
				return (false);
		}
		else
			dot++;
		if (dot > 1)
			return (false);
		i++;
		if (value[i] == '\n')
			value[i] = '\0';
	}
	return (true);
}

bool	check_camera(char **value, t_data *data)
{
	t_objs	*camera;

	if (check_nb_cam(data) == false)
		return (false);
	if (check_nb_params(value, 4, data) == false)
		return (false);
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (three_params_float(value[2], &data->scene) == false)
		return (false);
	if (check_isdigit_int(value[3], &data->scene) == false)
		return (false);
	camera = lst_new_objs();
	if (!camera)
		return (false);
	if (set_camera(camera, value, data) == false)
	{
		free(camera);
		return (false);
	}
	return (true);
}

bool	check_ambiant(char **value, t_data *data)
{
	t_objs	*ambiant;

	if (check_nb_ambiant(data) == false)
		return (false);
	if (count_params(value) != 3)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2 "Wrong number of \
		parameters for Ambiant\n\x1B[0m", data->scene.fname, data->scene.line);
		return (false);
	}
	if (check_isdigit_float(value[1]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Lightness must be a FLOAT\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	if (three_params_int(value[2], &data->scene) == false)
		return (false);
	ambiant = lst_new_objs();
	if (!ambiant)
		return (false);
	if (set_ambiant(ambiant, value, data) == false)
		return (free(ambiant), false);
	return (true);
}

bool	check_light(char **value, t_data *data)
{
	t_objs	*light;

	if (check_nb_light(data) == false)
		return (false);
	if (check_nb_params(value, 3, data) == false)
		return (false);
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (check_isdigit_float(value[2]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Lightness must be a FLOAT\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	light = lst_new_objs();
	if (!light)
		return (false);
	if (set_light(light, value, data) == false)
	{
		free(light);
		return (false);
	}
	return (true);
}
