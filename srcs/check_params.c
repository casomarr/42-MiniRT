/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:12:56 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/12 15:32:26 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_params(char **value)
{
	int	i;

	i = 0;
	while (value[i])
		i++;
	return (i);
}

bool	three_params_int(char *value, t_scene *scene)
{
	int		i;
	char	**params;

	i = 0;
	params = ft_split(value, ',');
	if (!params)
		return (false);
	if (count_params(params) != 3)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters\n\x1B[0m",\
			scene->fname, scene->line);
		ft_free_split(params);
		return (false);
	}
	while (params[i])
	{
		if (check_isdigit_int(params[i], scene) == false)
		{
			ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
				"number is not an INT\n\x1B[0m",\
				scene->fname, scene->line);
			ft_free_split(params);
			return (false);
		}
		if (ft_strlen(params[i]) >= 4)
		{
			ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
				"Wrong lenght colors parameters\n\x1B[0m", scene->fname, scene->line);
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params);
	return (true);
}

bool	three_params_float(char *value, t_scene *scene)
{
	char	**params;
	int		i;

	i = 0;
	params = ft_split(value, ',');
	if (count_params(params) != 3)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters\n\x1B[0m",\
			scene->fname, scene->line);
		ft_free_split(params);
		return (false);
	}
	while (params[i])
	{
		if (check_isdigit_float(params[i]) == false)
		{
			ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
				"number is not a FLOAT\n\x1B[0m",\
				scene->fname, scene->line);
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params);
	return (true);
}


bool	check_isdigit_int(char *value, t_scene *scene)
{
	int	i;

	i = 0;
	if (ft_is_sign(value[i]))
		i++;
	while (value[i] != '\0' && value[i] != '\n')
	{
		if (ft_isdigit(value[i]) == false)
		{
			ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
				"number is not an INT\n\x1B[0m",\
				scene->fname, scene->line);
			return (false);
		}
		i++;
	}
	if (value[i] == '\n')
		value[i] = '\0';
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
	while (value[i] != '\0' && value[i] != '\n')
	{
		if (value[i] != '.')
		{
			if (ft_isdigit(value[i]) == false)
				return (false);
		}
		else
			dot++;
		if (dot > 1)
			return (false);
		i++;
		if (value[i] == '\n')
			value[i] = '\0';
	}
	return (true);
}
