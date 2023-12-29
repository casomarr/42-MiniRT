/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:03:57 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/19 18:42:24 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Pour eviter des operations intermediaires je pourrai
convertir toutes ces fonctions en fonctions variadiques
pour pouvoir par exemple multiplier plus de seulement 2
vecteurs a la fois. */

t_vec	create_vec(int x, int y, int z)
{
	t_vec vector;
	
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/*Function to subtract two vectors*/
t_vec	vecSubstract(t_vec a, t_vec b)
{
	t_vec result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/*Function to add two vectors*/
t_vec	vecAdd(t_vec a, t_vec b)
{
	t_vec result;
	
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/*Function to multiply two vectors*/
t_vec	vecMultiply(t_vec a, t_vec b)
{
	t_vec result;
	
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

/*Function to multiply two vectors*/
t_vec	vecMultiplyFloat(t_vec a, float f)
{
	t_vec result;
	
	result.x = a.x * f;
	result.y = a.y * f;
	result.z = a.z * f;
	return (result);
}

t_vec	vecSquared(t_vec a)
{
	t_vec result;
	
	result.x = powf(a.x, 2);
	result.y = powf(a.y, 2);
	result.z = powf(a.z, 2);
	return (result);
}

t_vec	vecSqrt(t_vec a)
{
	t_vec result;
	
	result.x = sqrtf(a.x);
	result.y = sqrtf(a.y);
	result.z = sqrtf(a.z);
	return (result);
}

//pour vecteur normaliser vecteurs pour la norme
t_vec	vecDotProduct(t_vec a, t_vec b)
{
	t_vec result;
	
	//??
	return (result);
}
