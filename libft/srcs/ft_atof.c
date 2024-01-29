/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:07:30 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/12 15:07:43 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	int		reti;
	float	dec;
	float	sign;

	sign = 1;
	dec = 0;
	reti = 0;
	if (*str == '-') //TODO CHECK IF + IT'S OK BUT I DON'T THINK SO
	{
		sign = -1.;
		str++;
	}
	while (*str)
	{
		if (*str != '.')
		{
			dec *= 10;
			reti *= 10;
			reti += (int)(*str - '0');
		}
		else
			dec = 1;
		str++;
	}
	if (dec > 0)
		return (((float)reti * sign) / dec);
	return ((float)reti * sign);
}
