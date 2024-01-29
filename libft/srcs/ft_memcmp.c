/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octonaute <octonaute@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:04:13 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/25 18:06:24 by octonaute        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pt1, const void *pt2, size_t size)
{
	unsigned long	pos;
	int				delta;

	pos = 0;
	while (pos < size)
	{
		pos++;
		delta = *(unsigned char *)pt1++ - *(unsigned char *)pt2++;
		if (delta)
			return (delta);
	}
	return (0);
}
