/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/13 18:58:40 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_nb_value(char **value)
{
	int i;

	i = 0;
	while (value[i])
		i++;
	return (i);
}

bool	ft_isfloat(char *str)
{
	int	i;
	char	**nb_no_dot;
	int	sign;

	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	nb_no_dot = ft_split(str, '.');
	if (nb_no_dot == NULL)
	{
		ft_dprintf(2, "Error\nMalloc failed\n");
		return (false);
	}
	if (check_nb_value(nb_no_dot) != 2)
	{
		//ft_free_split(nb_no_dot);
		return (false);
	}
	return (true);
}

bool	check_three_floats(char *value)
{
	char	**numbers;

	numbers = ft_split(value, ',');
	if (numbers == NULL)
	{
		ft_dprintf(2, "Error\nMalloc failed\n");
		return (false);
	}
	int i = check_nb_value(numbers);
	if (i != 3)
	{
		ft_dprintf(2, "Error\nNb of args for position are wrong\n");
		//ft_free_split(numbers);
		return (false);
	}
	if (ft_isfloat(numbers[0]) == false)
	{
		ft_dprintf(2, "Error\nBad args\n");
		//ft_free_split(numbers);
		return (false);
	}
	return (true);
}

bool	check_camera(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	if (check_nb_value(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of values for camera\n");
		return (false);
	}
	if (check_three_floats(value[1]) == false)
		return (false);
	return (true);
}














































bool	check_ambient(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}


bool	check_light(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_sphere(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_plan(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}

bool	check_cylinder(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	while (value[i])
	{
		printf("%s\n", value[i]);
		i++;
	}
	return (true);
}
