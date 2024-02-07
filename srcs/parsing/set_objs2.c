/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:16:18 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/07 17:30:11 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	set_cylinder(t_objs *cylinder, char **value, t_data *data)
{
	t_objs	*tmp;

	cylinder->type = 1;
	if (get_tvec_from_str(value[1], &cylinder->pos) == false)
		return (false);
	if (get_tvec_from_str(value[2], &cylinder->dir) == false)
		return (false);
	cylinder->diameter = ft_atof(value[3]);
	cylinder->height = ft_atof(value[4]);
	if (get_trgb_from_str(value[5], &cylinder->color, &data->scene) == false)
		return (false);
	if (check_data_objs(cylinder, &data->scene) == false)
	{
		free(cylinder);
		return (false);
	}
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cylinder;
	}
	else
		data->scene.objs = cylinder;
	return (true);
}
