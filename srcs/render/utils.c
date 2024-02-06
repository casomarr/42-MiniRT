/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:23:42 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/02 18:30:11 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	create_vec(float x, float y, float z) //essayer de remplacer par (t_vec){x, y, z} ou pour lisibiliter remplacer les (t_vec){} par ça
{
	t_vec vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_objs	*get_node(t_objs *objs, int type)
{
	t_objs	*current;

	current = objs;
	while (current)
	{
		if (current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}
