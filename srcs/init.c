/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:09:34 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/12 14:12:23 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_data *data)
{
	data->scene.nb_camera = 0;
	data->scene.nb_ambiant = 0;
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
	new->position.x = 0;
	new->position.y = 0;
	new->position.z = 0;
	new->direction.x = 0;
	new->direction.y = 0;
	new->direction.z = 0;
	new->color.full = 0;
	new->diameter = 0;
	new->height = 0;
	new->fov = 0;
	new->lightness = 0;
	new->next = NULL;
	return (new);
}
