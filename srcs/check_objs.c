/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/05 17:59:58 by amugnier         ###   ########.fr       */
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
	}
	return (true);
}

bool	three_params_int(char *value)
{
	int		i;
	char	**params;

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
	while (params[i])
	{
		if (check_isdigit_int(params[i]) == false)
		{
			ft_dprintf(2, "Error\nWrong parameters\n");
			ft_free_split(params);
			return (false);
		}
		if (ft_strlen(params[i]) >= 4)
		{
			ft_dprintf(2, "Error\nWrong lenght colors parameters\n");
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params);
	return (true);
}

bool	three_params_float(char *value)
{
	int		i;
	char	**params;

	i = 0;
	params = ft_split(value, ',');
	if (count_params(params) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters\n");
		ft_free_split(params);
		return (false);
	}
	while (params[i])
	{
		if (check_isdigit_float(params[i]) == false)
		{
			ft_dprintf(2, "Error\nWrong parameters\n");
			ft_free_split(params);
			return (false);
		}
		i++;
	}
	ft_free_split(params);
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

// float	ft_atof(char *str)
// {
// 	int	i;
// 	int	sign;
// 	float	res;
// 	float dec;

// 	i = 0;
// 	sign = 1;
// 	res = 0;
// 	dec = 1;
// 	if (str[i] == '-')
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	while (str[i] != '.' && str[i] != '\0')
// 	{
// 		res = res * 10 + str[i] - '0';
// 		i++;
// 	}
// 	if (str[i] == '.')
// 	{
// 		i++;
// 		while (str[i] != '\0')
// 		{
// 			dec /= 10;
// 			res = res + (str[i] - '0') * dec;
// 			i++;
// 		}
// 	}
// 	return (res * sign);
// }

float	ft_atof(char *str)
{
	int		reti;
	float	dec;
	float	sign;

	sign = 1;
	dec = 0;
	reti = 0;
	if (*str == '-')
	{
		sign = -1.;
		str++;
	}
	while (*str)
	{
		if (*str != '.')
		{
			dec *= 10;
			reti *= 10;
			reti += (int)(*str - '0');
		}
		else
			dec = 1;
		str++;
	}
	if (dec > 0)
		return (((float)reti * sign) / dec);
	return ((float)reti * sign);
}

bool	get_tvec_from_str(char *str, t_vec *v)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (false);
	v->x = ft_atof(split[0]);
	v->y = ft_atof(split[1]);
	v->z = ft_atof(split[2]);
	ft_free_split(split);
	return (true);
}

bool	get_trgb_from_str(char *str, t_rgb *rgb)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (false);
	rgb->full = 0;
	rgb->argb[0] = (t_uint8)ft_atoi(split[0]);
	rgb->argb[1] = (t_uint8)ft_atoi(split[1]);
	rgb->argb[2] = (t_uint8)ft_atoi(split[2]);
	ft_free_split(split);
	return (true);
}

bool	check_camera(char **value, t_data *data)
{
	t_objs	*tmp;
	t_objs	*camera;//TODO check to free if error
	//TODO talk about incrementation of nb_objs
	data->scene.nb_camera++;
	if (data->scene.nb_camera > 1)
	{
		ft_dprintf(2, "Error\nOnly one camera is allowed\n");
		return (false);
	}
	if (count_params(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for camera\n");
		return (false);
	}
	if (three_params_float(value[1]) == false)
		return (false);
	if (three_params_float(value[2]) == false)
		return (false);
	if (check_isdigit_int(value[3]) == false)
		return (false);
	camera = lst_new_objs();
	if (!camera)
		return (false);
	camera->type = 3;
	if (get_tvec_from_str(value[1], &camera->position) == false)
		return (false);
	if (get_tvec_from_str(value[2], &camera->direction) == false)
		return (false);
	camera->fov = ft_atoi(value[3]);
	if (check_data_objs(camera) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = camera;
	}
	else
		data->scene.objs = camera;
	return (true);
}

bool	check_ambiant(char **value, t_data *data)
{
	t_objs	*tmp;
	t_objs	*ambiant;
	//TODO check to free if error
	data->scene.nb_ambiant++;
	if (data->scene.nb_ambiant > 1)
	{
		ft_dprintf(2, "Error\nOnly one ambiant is allowed\n");
		return (false);
	}
	if (count_params(value) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for ambiant\n");
		return (false);
	}
	if (check_isdigit_float(value[1]) == false)
		return (false);
	if (three_params_int(value[2]) == false)
		return (false);
	ambiant = lst_new_objs();
	if (!ambiant)
		return (false);
	ambiant->type = 4;
	ambiant->lightness = ft_atof(value[1]);
	if (get_trgb_from_str(value[2], &ambiant->color) == false)
		return (false);
	if (check_data_objs(ambiant) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ambiant;
	}
	else
		data->scene.objs = ambiant;
	return (true);
}

bool	check_light(char **value, t_data *data)
{
	t_objs	*tmp;
	t_objs	*light;
	//TODO check to free if error
	data->scene.nb_light++;
	if (data->scene.nb_light > 1)
	{
		ft_dprintf(2, "Error\nOnly one light is allowed\n");
		return (false);
	}
	if (count_params(value) != 3)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for light\n");
		return (false);
	}
	if (three_params_float(value[1]) == false)
		return (false);
	if (check_isdigit_float(value[2]) == false)
		return (false);
	light = lst_new_objs();
	if (!light)
		return (false);
	light->type = 5;
	if (get_tvec_from_str(value[1], &light->position) == false)
		return (false);
	light->lightness = ft_atof(value[2]);
	if (check_data_objs(light) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = light;
	}
	else
		data->scene.objs = light;
	return (true);
}

t_objs	*lst_new_objs(void)
{
	t_objs	*new;

	new = malloc(sizeof(t_objs));
	if (!new)
		return (NULL);
	new->type = 0;
	new->position.x = 0;
	new->position.y = 0;
	new->position.z = 0;
	new->direction.x = 0;
	new->direction.y = 0;
	new->direction.z = 0;
	new->color.full = 0;
	new->diameter = 0;
	new->height = 0;
	new->fov = 0;
	new->lightness = 0;
	new->next = NULL;
	return (new);
}

bool	check_sphere(char **value, t_data *data)
{
	t_objs	*tmp	;
	t_objs	*sphere;
	//TODO	check to free if error
	data->scene.nb_objs++;
	if (count_params(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for sphere\n");
		return (false);
	}
	if (three_params_float(value[1]) == false) //position
		return (false);
	if (check_isdigit_float(value[2]) == false) //diameter
		return (false);
	if (three_params_int(value[3]) == false) //color
		return (false);
	sphere = lst_new_objs();
	if (!sphere)
		return (false);
	sphere->type = 0;
	if (get_tvec_from_str(value[1], &sphere->position) == false)
		return (false);
	sphere->diameter = ft_atof(value[2]);
	if (get_trgb_from_str(value[3], &sphere->color) == false)
		return (false);
	if (check_data_objs(sphere) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = sphere;
	}
	else
		data->scene.objs = sphere;
	return (true);
}

bool	check_plan(char **value, t_data *data)
{
	t_objs	*tmp;
	t_objs	*plan;
	//TODO check to free if error
	data->scene.nb_objs++;
	if (count_params(value) != 4)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for plan\n");
		return (false);
	}
	if (three_params_float(value[1]) == false)
		return (false);
	if (three_params_float(value[2]) == false)
		return (false);
	if (three_params_int(value[3]) == false)
		return (false);
	plan = lst_new_objs();
	if (!plan)
		return (false);
	plan->type = 2;
	if (get_tvec_from_str(value[1], &plan->position) == false)
		return (false);
	if (get_tvec_from_str(value[2], &plan->direction) == false)
		return (false);
	if (get_trgb_from_str(value[3], &plan->color) == false)
		return (false);
	if (check_data_objs(plan) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = plan;
	}
	else
		data->scene.objs = plan;
	return (true);
}

bool	check_cylinder(char **value, t_data *data)
{
	t_objs	*cylinder; //TODO check to free if error
	t_objs	*tmp;

	data->scene.nb_objs++;
	if (count_params(value) != 6)
	{
		ft_dprintf(2, "Error\nWrong number of parameters for cylinder\n");
		return (false);
	}
	if (three_params_float(value[1]) == false)
		return (false);
	if (three_params_float(value[2]) == false)
		return (false);
	if (check_isdigit_float(value[3]) == false)
		return (false);
	if (check_isdigit_float(value[4]) == false)
		return (false);
	if (three_params_int(value[5]) == false)
		return (false);
	cylinder = lst_new_objs();
	if (!cylinder)
		return (false);
	cylinder->type = 1;
	if (get_tvec_from_str(value[1], &cylinder->position) == false)
		return (false);
	if (get_tvec_from_str(value[2], &cylinder->direction) == false)
		return (false);
	cylinder->diameter = ft_atof(value[3]);
	cylinder->height = ft_atof(value[4]);
	if (get_trgb_from_str(value[5], &cylinder->color) == false)
		return (false);
	if (check_data_objs(cylinder) == false)
		return (false);
	tmp = data->scene.objs;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cylinder;
	}
	else
		data->scene.objs = cylinder;
	return (true);
}
