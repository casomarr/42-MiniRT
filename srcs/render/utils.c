/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:23:42 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/08 15:53:13 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the node we are looking for */
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
