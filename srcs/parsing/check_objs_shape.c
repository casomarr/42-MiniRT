/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:33:01 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/08 16:00:40 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_sphere(char **value, t_data *data)
{
	t_objs	*sphere;

	data->scene.nb_objs++;
	if (check_nb_params(value, 4, data) == false)
		return (false);
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (check_isdigit_float(value[2]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Diameter must be a FLOAT\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	if (three_params_int(value[3], &data->scene) == false)
		return (false);
	sphere = lst_new_objs();
	if (!sphere)
		return (false);
	if (set_sphere(sphere, value, data) == false)
	{
		free(sphere);
		return (false);
	}
	return (true);
}

bool	check_plan(char **value, t_data *data)
{
	t_objs	*plan;

	data->scene.nb_objs++;
	if (check_nb_params(value, 4, data) == false)
		return (false);
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (three_params_float(value[2], &data->scene) == false)
		return (false);
	if (three_params_int(value[3], &data->scene) == false)
		return (false);
	plan = lst_new_objs();
	if (!plan)
		return (false);
	if (set_plan(plan, value, data) == false)
	{
		free(plan);
		return (false);
	}
	return (true);
}

bool	check_value_cylinder(char **value, t_data *data)
{
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (three_params_float(value[2], &data->scene) == false)
		return (false);
	if (check_isdigit_float(value[3]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Diameter must be a FLOAT\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	if (check_isdigit_float(value[4]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Height must be a FLOAT\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	if (three_params_int(value[5], &data->scene) == false)
		return (false);
	return (true);
}

bool	check_cylinder(char **value, t_data *data)
{
	t_objs	*cylinder;

	data->scene.nb_objs++;
	if (check_nb_params(value, 6, data) == false)
		return (false);
	if (check_value_cylinder(value, data) == false)
		return (false);
	cylinder = lst_new_objs();
	if (!cylinder)
		return (false);
	if (set_cylinder(cylinder, value, data) == false)
	{
		free(cylinder);
		return (false);
	}
	return (true);
}
