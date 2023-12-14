/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/14 17:16:47 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		count_params(char **value)
{
	int i;

	i = 0;
	while (value[i])
		i++;
	return (i);
}

bool	check_isdigit_int(char *value)
{
	int	i;

	i = 0;
	if (ft_is_sign(value[i]))
		i++;
	while (value[i] != '\0' && value[i] != '\n')
	{
		if (ft_isdigit(value[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_isdigit_float(char *value)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (ft_is_sign(value[i]))
		i++;
	while (value[i])
	{
		if (value[i] == '.')
		{
			dot++;
			i++;
		}
		if (dot > 1)
			return (false);
		if (ft_isdigit(value[i]) == false)
			return (false);
		i++;
	}
	return (true);
}


bool	three_params_int(char *value, t_data *data)
{
	int i;
	char **params;
	
	(void)data;
	i = 0;
	params = ft_split(value, ',');
	if (count_params(params) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters\n");
		ft_free_split(params);
		return (false);
	}
	while(params[i])
	{
		if (check_isdigit_int(params[i]) == false)
		{
			ft_dprintf(2, "Error\nWrong parameters\n");
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params);//TODO Remove this because i can't get the value in the function
	return (true);
}

bool	three_params_float(char *value, t_data *data)
{
	int i;
	char **params;
	
	(void)data;
	i = 0;
	params = ft_split(value, ','); //need free this at the end
	if (count_params(params) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters\n");
		ft_free_split(params);
		return (false);
	}
	while(params[i])
	{
		if (check_isdigit_float(params[i]) == false)
		{
			ft_dprintf(2, "Error\nWrong parameters\n");
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params); //TODO Remove this because i can't get the value in the function
	return (true);
}

bool	check_camera(char **value, t_data *data)
{
	int		i;

	i = 0;
	(void)data;
	if (count_params(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for camera\n");
		return (false);
	}
	if (three_params_float(value[1], data) == false)
		return (false);
	if (three_params_float(value[2], data) == false)
		return (false);
	if (check_isdigit_int(value[3]) == false)
		return (false);
	printf("Camera OK\n\n");
	return (true);
}

bool	check_ambient(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	if (count_params(value) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for ambient\n");
		return (false);
	}
	if (check_isdigit_float(value[1]) == false)
		return (false);
	if (three_params_int(value[2], data) == false)
		return (false);
	printf("Ambient OK\n\n");
	return (true);
}

bool	check_light(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	if (count_params(value) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for light\n");
		return (false);
	}
	if (three_params_float(value[1], data) == false)
		return (false);
	if (check_isdigit_float(value[2]) == false)
		return (false);
	printf("Light OK\n\n");
	return (true);
}


bool	check_sphere(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	if (count_params(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for sphere\n");
		return (false);
	}
	if (three_params_float(value[1], data) == false)
		return (false);
	if (check_isdigit_float(value[2]) == false)
		return (false);
	if (three_params_int(value[3], data) == false)
		return (false);
	printf("Sphere OK\n\n");
	return (true);
}

bool	check_plan(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	if (count_params(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for plan\n");
		return (false);
	}
	if (three_params_float(value[1], data) == false)
		return (false);
	if (three_params_float(value[2], data) == false)
		return (false);
	if (three_params_int(value[3], data) == false)
		return (false);
	printf("Plan OK\n\n");
	return (true);
}

bool	check_cylinder(char **value, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	if (count_params(value) != 6)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for cylinder\n");
		return (false);
	}
	if (three_params_float(value[1], data) == false)
		return (false);
	if (three_params_float(value[2], data) == false)
		return (false);
	if (check_isdigit_float(value[3]) == false)
		return (false);
	if (check_isdigit_float(value[4]) == false)
		return (false);
	if (three_params_int(value[5], data) == false)
		return (false);
	return (true);
}
