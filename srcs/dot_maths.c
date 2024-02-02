/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:03:57 by casomarr          #+#    #+#             */
/*   Updated: 2024/02/02 18:29:10 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//produit scalaire 
float	dot_product(t_vec a, t_vec b)
{
	return ((float)(a.x * b.x + a.y * b.y + a.z * b.z));
}

float	dot_product_float(t_vec b, float a)
{
	return (a * b.x + a * b.y + a * b.z);
}
//magnitude
float	vec_pythagore(t_vec a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec vec_cross(t_vec a, t_vec b) {
	t_vec result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}
