/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:07:30 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/08 14:55:38 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	process_before_comma(const char *str)
{
	float	result;
	char	*string;

	string = (char *)str;
	result = (float)ft_atoi(str);
	return (result);
}

static float	convert_to_float(const char *str)
{
	float	bef_comma;
	float	decimal;
	int		len;
	int		i;

	i = 0;
	bef_comma = process_before_comma(str);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		i++;
	decimal = (float)ft_atoi(&str[i]);
	len = ft_strlen(&str[i]);
	while (len--)
		decimal /= 10;
	if (bef_comma >= 0)
		return (bef_comma + decimal);
	else
		return (bef_comma + -decimal);
}

//Convert a string to a floating-point number.
float	ft_atof(const char *str)
{
	return (convert_to_float(str));
}
