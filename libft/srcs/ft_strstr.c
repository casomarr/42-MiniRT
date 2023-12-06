/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:04:59 by amugnier          #+#    #+#             */
/*   Updated: 2023/02/06 11:08:11 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(const char *str, char *comp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '\0' && comp[j] == '\0')
		return (EXIT_SUCCESS);
	while (str[i] != '\0')
	{
		while (str[i + j] == comp[j] && str[i + j] != '\0' && comp[j] != '\0')
			j++;
		if (comp[j] == '\0' && str[i + j] == '\0')
			return (EXIT_SUCCESS);
		else
			j = 0;
		i++;
	}
	return (EXIT_FAILURE);
}
