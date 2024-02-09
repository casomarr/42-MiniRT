/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:09:34 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/09 22:07:14 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_data *data)
{
	data->scene.nb_camera = 0;
	data->scene.nb_ambient = 0;
	data->scene.nb_light = 0;
	data->scene.nb_objs = 0;
	data->scene.objs = NULL;
	data->scene.line = 1;
}

t_objs	*lst_new_objs(void)
{
	t_objs	*new;

	new = malloc(sizeof(t_objs));
	if (!new)
		return (NULL);
	new->type = 0;
	new->pos.x = 0;
	new->pos.y = 0;
	new->pos.z = 0;
	new->dir.x = 0;
	new->dir.y = 0;
	new->dir.z = 0;
	new->color.full = 0;
	new->diameter = 0;
	new->height = 0;
	new->fov = 0;
	new->lightness = 0;
	new->next = NULL;
	return (new);
}
