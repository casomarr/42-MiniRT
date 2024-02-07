/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrt_maths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:26:52 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/07 16:55:38 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Applies a power of two to each
component of the vector */
t_vec	vec_squared(t_vec a)
{
	t_vec	result;

	result.x = powf(a.x, 2);
	result.y = powf(a.y, 2);
	result.z = powf(a.z, 2);
	return (result);
}

/* Applies a square root to each
component of the vector */
t_vec	vec_sqrt(t_vec a)
{
	t_vec	result;

	result.x = sqrtf(a.x);
	result.y = sqrtf(a.y);
	result.z = sqrtf(a.z);
	return (result);
}
