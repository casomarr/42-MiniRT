/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:59:22 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/09 22:07:14 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	set_camera(t_objs *camera, char **value, t_data *data)
{
	t_objs	*tmp;

	camera->type = 3;
	if (get_tvec_from_str(value[1], &camera->pos) == false)
		return (false);
	if (get_tvec_from_str(value[2], &camera->dir) == false)
		return (false);
	camera->fov = ft_atoi(value[3]);
	if (check_data_objs(camera, &data->scene) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = camera;
	}
	else
		data->scene.objs = camera;
	return (true);
}

bool	set_ambient(t_objs *ambient, char **value, t_data *data)
{
	t_objs	*tmp;

	ambient->type = 4;
	ambient->lightness = ft_atof(value[1]);
	if (get_trgb_from_str(value[2], &ambient->color, &data->scene) == false)
		return (false);
	if (check_data_objs(ambient, &data->scene) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ambient;
	}
	else
		data->scene.objs = ambient;
	return (true);
}

bool	set_light(t_objs *light, char **value, t_data *data)
{
	t_objs	*tmp;

	light->type = 5;
	if (get_tvec_from_str(value[1], &light->pos) == false)
		return (false);
	light->lightness = ft_atof(value[2]);
	if (check_data_objs(light, &data->scene) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = light;
	}
	else
		data->scene.objs = light;
	return (true);
}

bool	set_sphere(t_objs *sphere, char **value, t_data *data)
{
	t_objs	*tmp;

	sphere->type = 0;
	if (get_tvec_from_str(value[1], &sphere->pos) == false)
		return (false);
	sphere->diameter = ft_atof(value[2]);
	if (get_trgb_from_str(value[3], &sphere->color, &data->scene) == false)
		return (false);
	if (check_data_objs(sphere, &data->scene) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = sphere;
	}
	else
		data->scene.objs = sphere;
	return (true);
}

bool	set_plan(t_objs *plan, char **value, t_data *data)
{
	t_objs	*tmp;

	plan->type = 2;
	if (get_tvec_from_str(value[1], &plan->pos) == false)
		return (false);
	if (get_tvec_from_str(value[2], &plan->dir) == false)
		return (false);
	if (get_trgb_from_str(value[3], &plan->color, &data->scene) == false)
		return (false);
	if (check_data_objs(plan, &data->scene) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = plan;
	}
	else
		data->scene.objs = plan;
	return (true);
}
