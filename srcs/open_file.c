/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:28 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/12 18:30:37 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_check_objs
{
	const char	*ref;
	bool		(*check)(char **value);
};


bool	check_ambient(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_camera(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_light(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_sphere(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_plan(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_cylinder(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

void	check_chars(char **value)
{
	static struct s_check_objs comp[6] = {{"A",check_ambient},
		{"C", check_camera}, {"L", check_light}, {"sp", check_sphere},
		{"pl", check_plan}, {"cy", check_cylinder}};
	int i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(value[0], comp[i].ref, ft_strlen(comp[i].ref)) == 0)
		{
			comp[i].check(value);
			return ;
		}
		i++;
	}
	ft_dprintf(2, "Error\nObject not exists\n");
	//
	// else if (ft_strncmp(value[0], "A", 1) == 0)
	// {
	// 	printf("Ambient light\n");
	// }
	// else if (ft_strncmp(value[0], "L", 1) == 0)
	// {
	// 	printf("Light\n");
	// }
}

bool	check_nb_char_in_line(char *line)
{
	char	**value;
	// int		i;

	value = ft_split(line, ' ');
	if (value == NULL)
	{
		ft_dprintf(2, "Error\nMalloc failed\n");
		return (false);
	}
	if (value[0] == NULL)
	{
		//ft_free_split(value);
		return (false);
	}
	if (ft_strlen(value[0]) == 1 || ft_strlen(value[0]) == 2)
		check_chars(value);
	else
	{
		ft_dprintf(2, "Error\nObject not exists\n");
		//ft_free_split(value);
		return (false);
	}
	return (true);
}

int	parse_file(int fd)
{
	char	*line;
	// int		res;

	line = get_next_line(fd);
	if (line != NULL)
	{
		while (line)
		{
			if (ft_strlen(line) > 1 && line[0] != '#')
			{
				if (check_nb_char_in_line(line) == false)
				{
					free(line);
					return (false);
				}
			}
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		return (true);
	}
	return (false);
}

bool	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
			parse_file(fd);
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

int	parsing(char *file_name)
{
	// if (check_filename(file_name) == false)
	// 	return (false);
	// else
	if (open_file(file_name) == false)
		return (false);
	return (true);
}
