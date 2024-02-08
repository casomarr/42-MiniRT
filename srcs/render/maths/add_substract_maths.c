/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_substract_maths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:23:49 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/08 15:43:28 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Function to subtract two vectors */
t_vec	vec_substract(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/* Function to subtract a value
to each component of the vector */
t_vec	vec_substract_float(t_vec a, float b)
{
	t_vec	result;

	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	return (result);
}

/* Function to add two vectors */
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/* Function to add a value to each
component of the vector */
t_vec	vec_add_float(t_vec vec, float nb)
{
	t_vec	res;

	res.x = vec.x + nb;
	res.y = vec.y + nb;
	res.z = vec.z + nb;
	return (res);
}

/* Returns the length of a vector */
float	vec_length(t_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
