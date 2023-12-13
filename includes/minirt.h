/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/13 18:50:48 by amugnier         ###   ########.fr       */
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


typedef struct s_camera
{
	int		fov;
	float	coord_x;
	float	coord_y;
	float	coord_z;
	float	vector_x;
	float	vector_y;
	float	vector_z;
} t_camera;

typedef struct s_data
{
	t_camera	camera;
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
void	check_chars(char **value, t_data *data);

bool	check_camera(char **value, t_data *data);
bool	check_ambient(char **value, t_data *data);
bool	check_light(char **value, t_data *data);
bool	check_plan(char **value, t_data *data);
bool	check_sphere(char **value, t_data *data);
bool	check_cylinder(char **value, t_data *data);

#endif
