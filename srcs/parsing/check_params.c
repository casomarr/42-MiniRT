/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:12:56 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/08 15:39:31 by amugnier         ###   ########.fr       */
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

bool	check_status_int(char **params, t_scene *scene, int i)
{
	if (check_isdigit_int(params[i], scene) == false)
	{
		ft_free_split(params);
		return (false);
	}
	if (check_ovf_int(params[i], scene, 4) == false)
	{
		ft_free_split(params);
		return (false);
	}
	return (true);
}

bool	check_ovf_int(char *value, t_scene *scene, size_t size)
{
	if (ft_strlen(value) > size)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Args too long\n\x1B[0m", scene->fname, scene->line);
		return (false);
	}
	return (true);
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
			"Wrong number of parameters\n\x1B[0m", \
			scene->fname, scene->line);
		ft_free_split(params);
		return (false);
	}
	while (params[i])
	{
		if (check_status_int(params, scene, i) == false)
			return (false);
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
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2 "Wrong number \
		of parameters\n\x1B[0m", scene->fname, scene->line);
		ft_free_split(params);
		return (false);
	}
	while (params[i])
	{
		if (check_isdigit_float(params[i]) == false)
		{
			ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2 "number is \
			not a FLOAT\n\x1B[0m", scene->fname, scene->line);
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params);
	return (true);
}
