/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/16 20:41:27 by amugnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# define MAX_OBJ 256

typedef struct s_vec
{
	int x;
	int y;
	int z;
}	t_vec;

typedef struct s_light
{
	t_vec position;
	float lightness;
} t_light;

typedef struct s_ambiant
{
	float lightness;
	//RGB ??? int -> t_vec ou t_rgb ?
} t_ambiant;

typedef struct s_sphere
{
	t_vec position;
	float diameter;
	//RGB ??? int -> t_vec ou t_rgb ?
} t_sphere;

typedef struct s_cylinder
{
	t_vec position;
	t_vec direction;
	float diameter;
	float height;
	//RGB ??? int -> t_vec ou t_rgb ?
} t_cylinder;

typedef struct s_plan
{
	t_vec position;
	t_vec direction;
	//RGB ??? int -> t_vec ou t_rgb ?
} t_plan;

typedef struct s_camera
{
	t_vec	position;
	t_vec	direction;
	int		fov;
} t_camera;

typedef struct s_scene
{
	t_camera	camera;
	t_ambiant	ambiant;
	t_light		light;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plan		*plan;
	int			nb_sphere;
	int			nb_cylinder;
	int			nb_plan;
} t_scene;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_scene	scene;
} t_data;

typedef struct s_check_objs
{
	const char	*ref;
	bool		(*check)(char **value, t_data *data);
}				t_check_objs;

int		parse_file(int fd, t_data *data);
bool	check_not_empty(int fd);
bool	open_file(char *path, t_data *data);
int		parsing(char *file_name, t_data *data);
int		parse_file(int fd, t_data *data);
bool	check_nb_char_in_line(char *line, t_data *data);
bool	check_chars(char **value, t_data *data);

bool	check_camera(char **value, t_data *data);
bool	check_ambient(char **value, t_data *data);
bool	check_light(char **value, t_data *data);
bool	check_plan(char **value, t_data *data);
bool	check_sphere(char **value, t_data *data);
bool	check_cylinder(char **value, t_data *data);
void	ft_free_split(char **value);

#endif
