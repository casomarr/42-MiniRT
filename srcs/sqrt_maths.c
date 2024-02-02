/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sqrt_maths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:26:52 by octonaute         #+#    #+#             */
/*   Updated: 2024/02/02 18:27:02 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_squared(t_vec a)
{
	t_vec result;
	
	result.x = powf(a.x, 2); //powf(a, 2) = a*a = a au carré
	result.y = powf(a.y, 2);
	result.z = powf(a.z, 2);
	return (result);
}

t_vec	vec_sqrt(t_vec a)
{
	t_vec result;
	
	result.x = sqrtf(a.x);
	result.y = sqrtf(a.y);
	result.z = sqrtf(a.z);
	return (result);
}
