/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:50:56 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/09 22:07:14 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_split(char **value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		free(value[i]);
		i++;
	}
	free(value);
}

bool	check_nb_char_in_line(char *line, t_data *data)
{
	char	**value;

	value = ft_split(line, ' ');
	if (value == NULL)
	{
		ft_dprintf(2, "Error\nMalloc failed\n");
		return (false);
	}
	if (value[0] == NULL)
		return (ft_free_split(value), false);
	if (ft_strlen(value[0]) == 1 || ft_strlen(value[0]) == 2)
	{
		if (check_chars(value, data) == false)
			return (ft_free_split(value), false);
	}
	else
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"not a valid object\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (ft_free_split(value), false);
	}
	ft_free_split(value);
	return (true);
}

bool	check_nb_objs(t_data *data)
{
	if (data->scene.nb_ambient != 1)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of AMBIENT light\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	if (data->scene.nb_camera < 1)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of CAMERA\n\x1B[0m", data->scene.fname, \
			data->scene.line);
		return (false);
	}
	return (true);
}

int	parse_file(int fd, t_data *data)
{
	char	*line;

	init_data(data);
	line = get_next_line(fd);
	if (line != NULL)
	{
		while (line)
		{
			if (ft_strlen(line) > 1 && line[0] != '#')
			{
				if (check_nb_char_in_line(line, data) == false)
					return (free(line), false);
			}
			free(line);
			line = get_next_line(fd);
			data->scene.line++;
		}
		free(line);
		if (check_nb_objs(data) == false)
			return (false);
		return (true);
	}
	ft_dprintf(2, ERROR_MSG1 "%s: " ERROR_MSG2
		"Empty file\n\x1B[0m", data->scene.fname);
	return (false);
}

bool	check_chars(char **value, t_data *data)
{
	int							i;
	static struct s_check_objs	comp[6] = {{"A", check_ambient},
	{"C", check_camera}, {"L", check_light}, {"sp", check_sphere},
	{"pl", check_plan}, {"cy", check_cylinder}};

	i = 0;
	if (data->scene.nb_objs > MAX_OBJS)
	{
		ft_dprintf(2, "Error\nToo many objects\n");
		return (false);
	}
	while (i < 6)
	{
		if (ft_strncmp(value[0], comp[i].ref, ft_strlen(value[0])) == 0)
			return (comp[i].check(value, data));
		i++;
	}
	if (value[0][ft_strlen(value[0]) - 1] == '\n')
		value[0][ft_strlen(value[0]) - 1] = '\0';
	ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2 \
	"not a valid object\n\x1B[0m", data->scene.fname, \
		data->scene.line);
	return (false);
}
