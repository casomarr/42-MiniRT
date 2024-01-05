/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:10:20 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/05 21:19:06 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_coords(t_objs *objs)//je separe Camera, Light, Ambiant, Plan, Sphere, Cylinder ou j appelle cette fonction pour tous ceux qui ont des coords ?
{
	if ((objs->position.x < -10000 || objs->position.x > 10000)
		|| (objs->position.y < -10000 || objs->position.y > 10000)
		|| (objs->position.z < -10000 || objs->position.z > 10000))
	{
		ft_dprintf(2, "Error\nPosition must be between -10000 and 10000\n");
		return (false);
	}
	return (true);
}

bool	check_diameter(t_objs *objs)
{
	if (objs->diameter <= 0 || objs->diameter > 50)
	{
		ft_dprintf(2, "Error\nDiameter must be between 0 and 50\n");
		return (false);
	}
	return (true);
}

bool	check_height(t_objs *objs)
{
	if (objs->height <= 0 || objs->height > 50)
	{
		ft_dprintf(2, "Error\nHeight must be between 0 and 50\n");
		return (false);
	}
	return (true);
}

bool	check_fov(t_objs *objs)
{
	if (objs->fov < 0 || objs->fov > 180)
	{
		ft_dprintf(2, "Error\nFov must be between 0 and 180\n");
		return (false);
	}
	return (true);
}

bool	check_vector(t_objs *objs)
{
	if ((objs->direction.x < -1 || objs->direction.x > 1)
		|| (objs->direction.y < -1 || objs->direction.y > 1)
		|| (objs->direction.z < -1 || objs->direction.z > 1))
	{
		ft_dprintf(2, "Error\nDirection must be between -1 and 1\n");
		return (false);
	}
	return (true);
}

bool check_lightness(t_objs *objs)
{
	if (objs->lightness < 0.0 || objs->lightness > 1.0)
	{
		ft_dprintf(2, "Error\nLightness must be between 0 and 1\n");
		return (false);
	}
	return (true);
}

bool	check_color(t_objs *objs)
{
	if ((objs->color.argb[0] < 0 || objs->color.argb[0] > 255)
		|| (objs->color.argb[1] < 0 || objs->color.argb[1] > 255)
		|| (objs->color.argb[2] < 0 || objs->color.argb[2] > 255))
	{
		ft_dprintf(2, "Error\nColor must be between 0 and 255\n");
		return (false);
	}
	return (true);
}

bool	check_data_objs(t_objs *objs)
{
	//TODO VOIR SI JE PEUX FAIRE UN SEUL RETURN AVEC TOUTES LES FONCTIONS DEDANS
	if (objs->type == 0)
	{
		if (!check_coords(objs) || !check_diameter(objs) || !check_color(objs))
			return (false);
	}
	else if (objs->type == 1)
	{
		if (!check_coords(objs) || !check_vector(objs) || !check_diameter(objs)
			|| !check_color(objs) || !check_height(objs))
			return (false);
	}
	else if (objs->type == 2)
	{
		if (!check_coords(objs) || !check_vector(objs) || !check_color(objs))
			return (false);
	}
	else if (objs->type == 3)
	{
		if (!check_coords(objs) || !check_vector(objs) || !check_fov(objs))
			return (false);
	}
	else if (objs->type == 4)
	{
		if (!check_coords(objs) || !check_color(objs) || !check_lightness(objs))
			return (false);
	}
	else if (objs->type == 5)
	{
		if (!check_color(objs) || !check_lightness(objs))
			return (false);
	}
	return (true);
}
