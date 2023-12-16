/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:28 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/16 20:51:43 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	open_file(char *path, t_data *data)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
			if (parse_file(fd, data) == false)
			{
				close(fd);
				return (false);
			}
			close(fd);
			return (true);
	}
	else
	{
		printf("Error\nCan't be open or don't exist\n");
		return (false);
	}
}

bool	check_filename(char *file_name)
{
	if (ft_strstr(file_name, ".rt") == EXIT_SUCCESS)
		return (true);
	printf("Error: file must be a .rt\n");
	return (false);
}

int	parsing(char *file_name, t_data *data)
{
	if (check_filename(file_name) == false)
		return (false);
	else
	if (open_file(file_name, data) == false)
		return (false);
	return (true);
}
