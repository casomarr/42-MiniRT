/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_divide_maths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/08 15:54:03 by casomarr         ###   ########.fr       */
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

/*Function to multiply a vector by a float*/
t_vec	vec_multiply_float(t_vec a, float f)
{
	t_vec	result;

	result.x = a.x * f;
	result.y = a.y * f;
	result.z = a.z * f;
	return (result);
}

/*Function to divide two vectors*/
t_vec	vec_divide(t_vec a, float f)
{
	t_vec	result;

	result.x = a.x / f;
	result.y = a.y / f;
	result.z = a.z / f;
	return (result);
}

/*Function to divide a vector by a float*/
float	vec_divide_float(t_vec a, float f)
{
	return (a.x / f + a.y / f + a.z / f);
}
