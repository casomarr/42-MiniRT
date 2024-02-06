/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:25:15 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/02 18:25:37 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	vec_compare(t_vec a, t_vec b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (true);
	return (false);
}

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

float	ft_fabs(float f)
{
	if (f < 0)
		return (f * -1.);
	return (f);
}
