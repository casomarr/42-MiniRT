/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:21:00 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/14 15:07:30 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int determine_color(t_data *data, int x, int y)
{
	int	tmp;
	int	color;
	
	tmp = x + WIN_WIDTH * y;
	x = tmp % WIN_WIDTH;
	y = tmp / WIN_WIDTH;

	printf("on est sur le pixel %d:%d\n", x, y);
	
	color = data->ray.color * data->img.tab[x][y]; //tab[x][y] correspnd a quoi?

	return (color);
}

