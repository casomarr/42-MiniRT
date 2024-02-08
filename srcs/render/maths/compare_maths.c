/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:25:15 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/08 16:14:06 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns true if two vectors are the same */
bool	vec_compare(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (true);
	return (false);
}

/* Returns a vector with the highest
values of vectors v1 and v2 */
t_vec	vec_max(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret = v1;
	if (v1.x < v2.x)
		ret.x = v2.x;
	if (v1.y < v2.y)
		ret.y = v2.y;
	if (v1.z < v2.z)
		ret.z = v2.z;
	return (ret);
}

/* Returns a vector with the lowest
values of vectors v1 and v2 */
t_vec	vec_min(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret = v1;
	if (v1.x > v2.x)
		ret.x = v2.x;
	if (v1.y > v2.y)
		ret.y = v2.y;
	if (v1.z > v2.z)
		ret.z = v2.z;
	return (ret);
}

/* Returns the absolute value of f */
float	ft_fabs(float f)
{
	if (f < 0)
		return (f * -1.);
	return (f);
}

/* Negates a vector's values */
t_vec	vec_negate(t_vec v)
{
	t_vec	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}
