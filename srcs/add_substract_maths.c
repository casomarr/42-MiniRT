/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_substract_maths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:23:49 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/02 18:24:44 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Function to subtract two vectors*/
t_vec	vec_substract(t_vec a, t_vec b)
{
	t_vec result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec	vec_substract_float(t_vec a, float b)
{
	t_vec result;

	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	return (result);
}

/*Function to add two vectors*/
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec result;
	
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec	vec_add_float(t_vec vec, float nb)
{
	t_vec	res;

	res.x = vec.x + nb;
	res.y = vec.y + nb;
	res.z = vec.z + nb;
	return (res);
}
