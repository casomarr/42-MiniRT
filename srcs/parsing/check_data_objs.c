/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:10:20 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/25 18:07:27 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_coords(t_objs *objs, t_scene *scene)//je separe Camera, Light, Ambiant, Plan, Sphere, Cylinder ou j appelle cette fonction pour tous ceux qui ont des coords ?
{
	if ((objs->pos.x < -10000 || objs->pos.x > 10000)
		|| (objs->pos.y < -10000 || objs->pos.y > 10000)
		|| (objs->pos.z < -10000 || objs->pos.z > 10000))
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Coords must be between -10000 and 10000\n\x1B[0m", scene->fname,\
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_diameter(t_objs *objs, t_scene *scene)
{
	if (objs->diameter <= 0 || objs->diameter > 200)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Diameter must be between 0 and 50\n\x1B[0m", scene->fname,\
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
			"Height must be between 0 and 50\n\x1B[0m", scene->fname,\
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_fov(t_objs *objs, t_scene *scene)
{
	if (objs->fov < 0 || objs->fov > 180)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Fov must be between 0 and 180\n\x1B[0m", scene->fname,\
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_vector(t_objs *objs, t_scene *scene)
{
	if ((objs->dir.x < -1 || objs->dir.x > 1)
		|| (objs->dir.y < -1 || objs->dir.y > 1)
		|| (objs->dir.z < -1 || objs->dir.z > 1))
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Vector must be between -1 and 1\n\x1B[0m", scene->fname,\
			scene->line);
		return (false);
	}
	return (true);
}

bool check_lightness(t_objs *objs, t_scene *scene)
{
	if (objs->lightness < 0.0 || objs->lightness > 1.0)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Lightness must be between 0.0 and 1.0\n\x1B[0m", scene->fname,\
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_color(t_objs *objs, t_scene *scene)
{
	if ((objs->color.bgra[0] < 0 || objs->color.bgra[0] > 255)
		|| (objs->color.bgra[1] < 0 || objs->color.bgra[1] > 255)
		|| (objs->color.bgra[2] < 0 || objs->color.bgra[2] > 255))
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Color must be between 0 and 255\n\x1B[0m", scene->fname,\
			scene->line);
		return (false);
	}
	return (true);
}

bool	check_data_objs(t_objs *objs, t_scene *scene)
{
	//TODO VOIR SI JE PEUX FAIRE UN SEUL RETURN AVEC TOUTES LES FONCTIONS DEDANS
	if (objs->type == 0)
	{
		if (!check_coords(objs, scene) || !check_diameter(objs, scene))
			return (false);
	}
	else if (objs->type == 1)
	{
		if (!check_coords(objs, scene) || !check_vector(objs, scene) || !check_diameter(objs, scene)
			|| !check_height(objs, scene))
			return (false);
	}
	else if (objs->type == 2)
	{
		if (!check_coords(objs, scene) || !check_vector(objs, scene))
			return (false);
	}
	else if (objs->type == 3)
	{
		if (!check_coords(objs, scene) || !check_vector(objs, scene) || !check_fov(objs, scene))
			return (false);
	}
	else if (objs->type == 4)
	{
		if (!check_coords(objs, scene) || !check_lightness(objs, scene))
			return (false);
	}
	else if (objs->type == 5)
	{
		if ( !check_coords(objs, scene) || !check_lightness(objs, scene))
			return (false);
	}
	return (true);
}
