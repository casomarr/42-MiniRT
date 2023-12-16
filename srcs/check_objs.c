/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/16 20:32:31 by amugnier         ###   ########.fr       */
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
	while (value[i] != '\0' && value[i] != '\n')
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
	if (!params)
		return (false);
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
/*

DEFINE OBJ_BUFF_SIZE 1024

t_scene{
	t_camera	*cam;
	t_ambiant	ambiant;
	t_light		light;
	t_plane		planes[OBJ_BUFF_SIZE]
}

t_data{
	t_scene scene;
}

t_vec3{
	float x;
	float y;
	float z;
}

t_camera{
	t_vec3	pos;
	t_vec3	dir;
	int		fov;
}

t_plane{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3i	color;
}


#            x  y  z          x  y  z               FOV           R G B
C
-50.0,0,20
0,0,1
70

pl          0.0,0.0,-10.0     0.0,1.0,0.0                         0,0,225

*/

// t_camera *get_camera_data(char **line){
// 	t_camera *ret;
// 	ret = malloc(sizeof(t_camera));
// 	if (!ret)
// 		return 0;
// 	/*
// 	récupérer les datas de t_vec3 line[1], t_vec3 line[2] et int line[3]
// 	*/
// 	return ret;
// }


bool	get_tvec_from_str(char *str, t_vec *v)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (false);
	v->x = ft_atoi(split[0]);
	v->y = ft_atoi(split[1]);
	v->z = ft_atoi(split[2]);
	//freesplit
	ft_free_split(split);
	return (true);
}

bool	check_camera(char **value, t_data *data)
{
	// int		i;

	// i = 0;
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
	if (get_tvec_from_str(value[1], &data->scene.camera.position) == false)
		return (false);
	if (get_tvec_from_str(value[2], &data->scene.camera.direction) == false)
		return (false);
	// printf("%d, %d, %d\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	// printf("%d, %d, %d\n", data->camera.direction.x, data->camera.direction.y, data->camera.direction.z);
	return (true);
}

bool	check_ambient(char **value, t_data *data)
{
	// int i;

	// i = 0;
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
	// int i;

	// i = 0;
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
	// int i;

	// i = 0;
	data->scene.nb_sphere++;
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
	// int i;

	// i = 0;
	data->scene.nb_plan++;
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
	// int i;

	// i = 0;
	data->scene.nb_cylinder++;
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
