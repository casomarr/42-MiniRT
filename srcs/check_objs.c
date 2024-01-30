/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:55:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/30 19:38:20 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* bool	check_isdigit_int(char *value, t_scene *scene)
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
} */

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
	if (*str == '-') //TODO CHECK IF + IT'S OK BUT I DON'T THINK SO
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

bool	check_camera(char **value, t_data *data)
{
	t_objs	*tmp;
	t_objs	*camera;//TODO check to free if error
	//TODO talk about incrementation of nb_objs
	data->scene.nb_camera++;
	if (data->scene.nb_camera > 1)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Only one camera is allowed\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (count_params(value) != 4)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters for Camera\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (three_params_float(value[2], &data->scene) == false)
		return (false);
	if (check_isdigit_int(value[3], &data->scene) == false) //TODO CALL ERROR MESSAGE
		return (false);
	camera = lst_new_objs();
	if (!camera)
		return (false);
	camera->type = 3;
	if (get_tvec_from_str(value[1], &camera->pos) == false)
		return (false);
	if (get_tvec_from_str(value[2], &camera->dir) == false)
		return (false);
	camera->fov = ft_atoi(value[3]);
	if (check_data_objs(camera, &data->scene) == false)
	{
		free(camera);
		return (false);
	}
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
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Only one ambiant is allowed\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (count_params(value) != 3)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters for Ambiant\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (check_isdigit_float(value[1]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Lightness must be a FLOAT\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_int(value[2], &data->scene) == false)
		return (false);
	ambiant = lst_new_objs();
	if (!ambiant)
		return (false);
	ambiant->type = 4;
	ambiant->lightness = ft_atof(value[1]);
	if (get_trgb_from_str(value[2], &ambiant->color, &data->scene) == false)
		return (false);
	if (check_data_objs(ambiant, &data->scene) == false)
	{
		free(ambiant);
		return (false);
	}
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
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Only one light is allowed\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (count_params(value) != 3)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters for Light\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (check_isdigit_float(value[2]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Lightness must be a FLOAT\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	light = lst_new_objs();
	if (!light)
		return (false);
	light->type = 5;
	if (get_tvec_from_str(value[1], &light->pos) == false)
		return (false);
	light->lightness = ft_atof(value[2]);
	if (check_data_objs(light, &data->scene) == false)
	{
		free(light);
		return (false);
	}
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

bool	check_sphere(char **value, t_data *data)
{
	t_objs	*tmp	;
	t_objs	*sphere;
	//TODO	check to free if error
	data->scene.nb_objs++;
	if (count_params(value) != 4)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters for Sphere\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_float(value[1], &data->scene) == false) //pos
		return (false);
	if (check_isdigit_float(value[2]) == false) //diameter
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Diameter must be a FLOAT\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_int(value[3], &data->scene) == false) //color
		return (false);
	sphere = lst_new_objs();
	if (!sphere)
		return (false);
	sphere->type = 0;
	if (get_tvec_from_str(value[1], &sphere->pos) == false)
		return (false);
	sphere->diameter = ft_atof(value[2]);
	if (get_trgb_from_str(value[3], &sphere->color, &data->scene) == false)
		return (false);
	if (check_data_objs(sphere, &data->scene) == false)
	{
		free(sphere);
		return (false);
	}
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
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters for Plan\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (three_params_float(value[2], &data->scene) == false)
		return (false);
	if (three_params_int(value[3], &data->scene) == false)
		return (false);
	plan = lst_new_objs();
	if (!plan)
		return (false);
	plan->type = 2;
	if (get_tvec_from_str(value[1], &plan->pos) == false)
		return (false);
	if (get_tvec_from_str(value[2], &plan->dir) == false)
		return (false);
	if (get_trgb_from_str(value[3], &plan->color, &data->scene) == false)
		return (false);
	if (check_data_objs(plan, &data->scene) == false)
	{
		free(plan);
		return (false);
	}
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
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Wrong number of parameters for Cylinder\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_float(value[1], &data->scene) == false)
		return (false);
	if (three_params_float(value[2], &data->scene) == false)
		return (false);
	if (check_isdigit_float(value[3]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Diameter must be a FLOAT\n\x1B[0m", data->scene.fname,\
			data->scene.line);
			return (false);
	}
	if (check_isdigit_float(value[4]) == false)
	{
		ft_dprintf(2, ERROR_MSG1 "%s:%d: " ERROR_MSG2
			"Height must be a FLOAT\n\x1B[0m", data->scene.fname,\
			data->scene.line);
		return (false);
	}
	if (three_params_int(value[5], &data->scene) == false)
		return (false);
	cylinder = lst_new_objs();
	if (!cylinder)
		return (false);
	cylinder->type = 1;
	if (get_tvec_from_str(value[1], &cylinder->pos) == false)
		return (false);
	if (get_tvec_from_str(value[2], &cylinder->dir) == false)
		return (false);
	cylinder->diameter = ft_atof(value[3]);
	cylinder->height = ft_atof(value[4]);
	if (get_trgb_from_str(value[5], &cylinder->color, &data->scene) == false)
		return (false);
	if (check_data_objs(cylinder, &data->scene) == false)
	{
		free(cylinder);
		return (false);
	}
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
