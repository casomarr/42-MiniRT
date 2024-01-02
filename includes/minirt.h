/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/02 17:45:47 by amugnier         ###   ########.fr       */
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

/*Patou : si le sujet ne specifie pas de taille d'image on
peut faire une image petite pour augmenter les fps.*/
# define WIN_HEIGHT 200
# define WIN_WIDTH 400

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define SPHERE		0
# define CYLINDER	1
# define PLANE		2
# define CAMERA		3
# define LIGHT		4
# define AMBIANT	5

typedef struct s_img
{
	void	*mlx_img; //address that mlx_new_image returns
	char	*addr;
	int		bpp; /* bits per pixel */
	int		width; //avant line_len, change pour ray_generation
	int		height;
	int		endian;
	//int		**tab;
}	t_img;

typedef struct s_vec
{
	float x;
	float y;
	float z;
}	t_vec;

typedef struct s_ray
{
	t_vec	origin; //le changer en "origin"? plus court et plus clair
	t_vec	current_pixel;
	t_vec	location;
	t_vec	object_direction;
	t_vec	light_direction;
	int		norm;
	int		color;
	float	pixel_delta_w;
	float	pixel_delta_h;
}	t_ray;


typedef unsigned char t_uint8;

typedef union u_rgb
{
	int		full;
	t_uint8	argb[4];
}	t_rgb;

typedef struct s_objs
{
	short			type; //a check 0 = sphere, 1 = plan, 2 = cylinder 3 = camera 4 = ambiant 5 = light
	t_vec			position; //all
	t_vec			direction; //plan and cylinder
	t_rgb			color;
	float			diameter; //sphere and cylinder
	float			height; //cylinder only
	int				fov; //camera only
	float			lightness; //ambiant and light
	struct s_objs	*next;
} t_objs;


typedef struct s_scene
{
	t_objs		*objs;
	int			nb_camera;
	int			nb_ambiant;
	int			nb_light;
	int			nb_objs;
} t_scene;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_ray	ray;
	t_scene	scene;
	int		current_pixel_color;
	int		x;
	int		y;
	int		z_index;
}	t_data;

typedef struct s_check_objs
{
	const char	*ref;
	bool		(*check)(char **value, t_data *data);
}				t_check_objs;

int		parse_file(int fd, t_data *data);
bool	check_not_empty(int fd);
bool	open_file(char *path, t_data *data);
int		parsing(char *file_name, t_data *data);
bool	check_nb_char_in_line(char *line, t_data *data);
bool	check_chars(char **value, t_data *data);
bool	check_camera(char **value, t_data *data);
bool	check_ambiant(char **value, t_data *data);
bool	check_light(char **value, t_data *data);
bool	check_plan(char **value, t_data *data);
bool	check_sphere(char **value, t_data *data);
bool	check_cylinder(char **value, t_data *data);
void	ft_free_split(char **value);
void	init_data(t_data *data);
t_objs	*lst_new_objs(void);
bool	check_coords(t_objs *objs);
bool	check_diameter(t_objs *objs);
bool	check_height(t_objs *objs);
bool	check_fov(t_objs *objs);
bool	check_vector(t_objs *objs);
bool	check_lightness(t_objs *objs);
bool	check_color(t_objs *objs);
bool	check_data_objs(t_objs *objs);



/*Main*/
int		initialisation(t_data *data);

/*Rays*/
void	ray_init(t_data *data);
void	ray_generation(t_data *data);
void	get_norm(t_data *data);

/*Vector Maths*/
t_vec	vecSubstract(t_vec a, t_vec b);
t_vec	vecAdd(t_vec a, t_vec b);
t_vec	vecMultiply(t_vec a, t_vec b);
t_vec	vecDotProduct(t_vec a, t_vec b);

/*Intersections*/
void	sphere_intersection(bool *intersection, t_data *data);
bool	intersection(t_data *data);

/*Color*/
bool	direct_light(t_data *data);
int		determine_pixel_color(t_data *data);
// void	determine_pixel(t_data *data);

/*Render*/
void	img_pix_put(t_data *data, int x, int y, int color);
void	add_pixel_to_img(t_data *data, int color);

/*Light Intensity*/
int		distance_light_object(t_data *data);
int		brdf(t_data *data);
int		shadows(t_data *data);

#endif
