/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:03:57 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/08 16:15:06 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Scalar product : returns the cosine of the angle between the
two vectors multiplied by the magnitudes of both vectors.*/
float	dot_product(t_vec a, t_vec b)
{
	return ((float)(a.x * b.x + a.y * b.y + a.z * b.z));
}

float	dot_product_float(t_vec b, float a)
{
	return (a * b.x + a * b.y + a * b.z);
}

/* Returns the length (also known as magnitude) of a vector */
float	vec_pythagore(t_vec a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

/* Computes the cross product of two vectors a and b,
resulting in a vector that is perpendicular to both a and b.*/
t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
