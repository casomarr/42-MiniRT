/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:03:57 by casomarr          #+#    #+#             */
/*   Updated: 2024/01/12 14:33:31 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*Pour eviter des operations intermediaires je pourrai
convertir toutes ces fonctions en fonctions variadiques
pour pouvoir par exemple multiplier plus de seulement 2
vecteurs a la fois. */

t_vec	create_vec(float x, float y, float z)
{
	t_vec vector;
	
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

/*Function to subtract two vectors*/
t_vec	vec_substract(t_vec a, t_vec b)
{
	t_vec result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/*Function to add two vectors*/
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec result;
	
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/*Function to multiply two vectors*/
t_vec	vec_multiply(t_vec a, t_vec b)
{
	t_vec result;
	
	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}

/*Function to multiply two vectors*/
t_vec	vec_multiply_float(t_vec a, float f)
{
	t_vec result;
	
	result.x = a.x * f;
	result.y = a.y * f;
	result.z = a.z * f;
	return (result);
}

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

//produit scalaire 
float	dot_product(t_vec a, t_vec b)
{
	return ((float)(a.x * b.x + a.y * b.y + a.z * b.z));
}

float	dot_product_float(t_vec b, float a)
{
	return (a * b.x + a * b.y + a * b.z);
}
float	vec_pythagore(t_vec a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}