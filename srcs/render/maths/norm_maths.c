/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_maths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:16:58 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/07 16:56:46 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the norm of a vector */
float	get_norm(t_vec vec)
{
	return (sqrtf(vec.x * vec.x + \
				vec.y * vec.y + \
				vec.z * vec.z));
}

/* Normalizes a vector (turns it into a length of 1) */
t_vec	vec_normalize(t_vec v)
{
	float	length;
	t_vec	result;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length != 0)
	{
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}
