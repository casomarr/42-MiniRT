/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:28 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/11 15:08:17 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	start_parsing(int fd)
{
	(void)fd;
	printf("Parsing...\n");
}

bool	check_not_empty(int fd)
{
	char	buffer[1];
	int		ret;

	ret = read(fd, buffer, 1);
	if (ret == 0)
	{
		printf("Error\nFile is empty\n");
		return (false);
	}
	else if (ret == -1)
	{
		perror("Error\n");
		return (false);
	}
	return (true);
}

bool	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		if (check_not_empty(fd) == false)
		{
			close(fd);
			return (false);
		}
		else
		{
			start_parsing(fd);
			return (true);
		}
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

int	parsing(char *file_name)
{
	if (check_filename(file_name) == false)
		return (false);
	else
		if (open_file(file_name) == false)
			return (false);
	return (true);
}
