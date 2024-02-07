/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_divide_maths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/07 17:16:01 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Function to multiply two vectors*/
t_vec	vec_multiply(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

/*Function to multiply two vectors*/
t_vec	vec_multiply_float(t_vec a, float f)
{
	t_vec	result;

	result.x = a.x * f;
	result.y = a.y * f;
	result.z = a.z * f;
	return (result);
}

t_vec	vec_divide(t_vec a, float f)
{
	t_vec	result;

	result.x = a.x / f;
	result.y = a.y / f;
	result.z = a.z / f;
	return (result);
}

float	vec_divide_float(t_vec a, float f)
{
	return (a.x / f + a.y / f + a.z / f);
}
