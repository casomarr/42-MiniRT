/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:50:56 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/14 17:05:21 by amugnier         ###   ########.fr       */
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
	{
		ft_free_split(value);
		return (false);
	}
	if (ft_strlen(value[0]) == 1 || ft_strlen(value[0]) == 2)
		check_chars(value, data); //NEED TO TRANSFORM THIS FUNCTION TO BOOL TO FREE IF ERROR
	else
	{
		ft_dprintf(2, "Error\nObject not exists\n");
		ft_free_split(value);
		return (false);
	}
	ft_free_split(value); //TODO Remove this because i can't get the value in the function
	return (true);
}

int	parse_file(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	if (line != NULL)
	{
		while (line)
		{
			if (ft_strlen(line) > 1 && line[0] != '#')
			{
				if (check_nb_char_in_line(line, data) == false)
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

void	check_chars(char **value, t_data *data) //change to bool return type
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
			comp[i].check(value, data); //add if false
			return ; 
		}
		i++;
	}
	ft_dprintf(2, "Error\nObject not exists\n"); //move this error
}
