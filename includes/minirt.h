/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/18 19:09:05 by amugnier         ###   ########.fr       */
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
# define MAX_OBJS 256

typedef struct s_vec
{
	float x;
	float y;
	float z;
}	t_vec;

typedef unsigned char t_uint8;

typedef union u_rgb
{
	int		full;
	t_uint8	argb[4];
}	t_rgb;

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

typedef struct s_camera
{
	t_vec	position;
	t_vec	direction;
	int		fov;
} t_camera;


typedef struct s_objs
{
	short			type; //a check 0 = sphere, 1 = plan, 2 = cylinder
	t_vec			position; //all 
	t_vec			direction; //plan and cylinder 
	t_rgb			color;
	float			diameter; //sphere and cylinder
	float			height; //cylinder only
	struct s_objs	*next;
} t_objs;


typedef struct s_scene
{
	t_camera	camera;
	t_ambiant	ambiant;
	t_light		light;
	t_objs		*objs;
	int			nb_camera;
	int			nb_ambiant;
	int			nb_light;
	int			nb_objs;
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
void	init_data(t_data *data);


#endif
