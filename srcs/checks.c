/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:03:56 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/13 19:41:22 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection(t_data *data, int j, int i)
{
	int	tmp;
	int	x;
	int	y;
	bool ret;

	ret  = false;
	//convertir tableau de couleurs en coordonnees (calcul patou discord)
	tmp = x + WIN_WIDTH * y;
	x = tmp % WIN_WIDTH;
	y = tmp / WIN_WIDTH;
	while (tmp < WIN_WIDTH * WIN_HEIGHT)
	{
		tmp++;
		x = tmp % WIN_WIDTH;
		y = tmp / WIN_WIDTH;
		printf("on est sur le pixel %d:%d\n", x, y)
		if (scene->objs.sphere > 0) // si il y a au moins une sphere dans la scene
				objects_iteration(&ret, spheres_intersection(), data->img.endian[x][y]); //je pense que c'est endian qui est le tableau de couleurs? pourtant c est pas un int * dans la struct??
		if (scene->objs.cylinder > 0) //ces structures n'existent pas encore, m'adapter a ce que m'enverra antoine
				objects_iteration(&ret, cylinder_intersection(), data->img.endian[x][y]);
		if (scene->objs.plane > 0)
				objects_iteration(&ret, plane_intersection(), data->img.endian[x][y]);
	}
	return (ret);
}
