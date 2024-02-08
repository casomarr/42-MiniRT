/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_objs2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:49:04 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/08 18:31:26 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_fov(t_objs *objs, t_scene *scene)
{
	if (objs->fov < 0 || objs->fov > 180)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Fov must be between 0 and 180\n\x1B[0m", scene->fname, \
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_lightness(t_objs *objs, t_scene *scene)
{
	if (objs->lightness < 0.0 || objs->lightness > 1.0)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Lightness must be between 0.0 and 1.0\n\x1B[0m", scene->fname, \
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_height(t_objs *objs, t_scene *scene)
{
	if (objs->height <= 0 || objs->height > 50)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Height must be between 0 and 50\n\x1B[0m", scene->fname, \
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_shape_objs(t_objs *objs, t_scene *scene)
{
	if (objs->type == 0)
	{
		if (!check_coords(objs, scene) || !check_diameter(objs, scene))
			return (false);
	}
	else if (objs->type == 1)
	{
		if (!check_coords(objs, scene) || !check_vector(objs, scene) \
			|| !check_diameter(objs, scene)
			|| !check_height(objs, scene))
			return (false);
	}
	else if (objs->type == 2)
	{
		if (!check_coords(objs, scene) || !check_vector(objs, scene))
			return (false);
	}
	return (true);
}
