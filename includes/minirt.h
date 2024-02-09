/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/09 20:38:51 by casomarr         ###   ########.fr       */
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
# include <float.h>

# define MAX_OBJS 256
# define PI 3.14159265358979323846

# define C_ATTENUATION 1.0
# define L_ATTENUATION 0.01
# define Q_ATTENUATION 0.0001


# define WIN_HEIGHT 800
# define WIN_WIDTH 800

# define SPHERE		0
# define CYLINDER	1
# define PLANE		2
# define CAMERA		3
# define AMBIENT	4
# define LIGHT		5

# define STOP 0
# define PARSING_ERROR 1

# define ESC_KEY 65307
# define KEY_M 109
# define KEY_R 114

# define MAX_DIST_CAMERA	FLT_MAX

# define ERROR_MSG1 "Error\n\x1B[1m"
# define ERROR_MSG2 "\x1B[31merror:\x1B[0m\x1B[1m "

typedef unsigned int	t_uint32;
typedef unsigned char	t_uint8;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef union u_color
{
	t_uint32	full;
	t_uint8		bgra[4];
}	t_color;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		width;
	int		height;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_objs
{
	short			type;
	t_vec			pos;
	t_vec			dir;
	t_color			color;
	float			diameter;
	float			height;
	int				fov;
	float			lightness;
	struct s_objs	*next;
}	t_objs;

typedef struct s_inter {
	t_ray	ray;
	t_vec	point;
	t_vec	normal;
	float	dist;
	t_objs	*obj;
}	t_inter;

typedef struct s_scene
{
	t_objs		*objs;
	t_objs		*cam;
	int			nb_camera;
	int			nb_ambiant;
	int			nb_light;
	int			nb_objs;
	int			line;
	char		*fname;
	t_vec		rdir;
	t_vec		udir;
}	t_scene;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_scene	scene;
	bool	render_ambiant;
}	t_data;
	
typedef bool			(*t_checkfunction)(char **value, t_data *data);

typedef struct s_check_objs
{
	const char		*ref;
	t_checkfunction	check;
}	t_check_objs;

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
bool	check_lightness(t_objs *objs, t_scene *scene);
bool	check_color(t_objs *objs, t_scene *scene);
bool	check_vector(t_objs *objs, t_scene *scene);
bool	check_fov(t_objs *objs, t_scene *scene);
bool	check_height(t_objs *objs, t_scene *scene);
bool	check_data_objs(t_objs *objs, t_scene *scene);
bool	check_diameter(t_objs *objs, t_scene *scene);
bool	check_coords(t_objs *objs, t_scene *scene);
int		count_params(char **value);
bool	check_isdigit_int(char *value, t_scene *scene);
bool	check_isdigit_float(char *value);
bool	three_params_float(char *value, t_scene *scene);
bool	three_params_int(char *value, t_scene *scene);
bool	get_tvec_from_str(char *str, t_vec *v);
bool	get_trgb_from_str(char *str, t_color *rgb, t_scene *scene);
bool	check_ovf_int(char *value, t_scene *scene, size_t size);
bool	check_nb_params(char **value, int nb_params, t_data *data);
bool	check_nb_cam(t_data *data);
bool	set_camera(t_objs *camera, char **value, t_data *data);
bool	set_ambiant(t_objs *ambiant, char **value, t_data *data);
bool	set_light(t_objs *light, char **value, t_data *data);
bool	set_sphere(t_objs *sphere, char **value, t_data *data);
bool	set_cylinder(t_objs *cylinder, char **value, t_data *data);
bool	check_value_cylinder(char **value, t_data *data);
bool	set_plan(t_objs *plan, char **value, t_data *data);
bool	check_nb_light(t_data *data);
bool	check_nb_ambiant(t_data *data);
bool	check_status_int(char **params, t_scene *scene, int i);
bool	check_is_not_comment(char *line, t_data *data);
bool	check_len_str(char **value, t_data *data);
int		change_ambiant_render(int keycode, t_data *data);
bool	check_shape_objs(t_objs *objs, t_scene *scene);
void	ft_stop(t_data *data, short error);

/*							RENDER FOLDER							*/

/* Color */
int		get_pixel_color(t_inter inter, t_objs *objects, \
t_data *data, t_ray ray);

/* Cylinder Check Hit */
float	check_hit_side(t_inter *inter, t_objs *cylinder);
float	check_hit_captop(t_inter *inter, t_objs *cylinder);
float	check_hit_capbottom(t_inter *inter, t_objs *cylinder);

/* Cylinder */
void	intersection_point_cylinder(t_inter *inter, t_objs *cylinder);

/* Intersections */
t_inter	closest_intersection(t_ray ray, t_objs *object, float dist);

/*Light Attenuation*/
t_vec	attenuate_color(t_vec color, float dist_light);

/* Plane */
void	intersection_point_plane(t_inter *inter, t_objs *plane);

/* Rays */
void	minirt(t_data *data);

/* Render */
void	img_pix_put(t_data *data, int x, int y, int color);

/* Sphere */
void	intersection_point_sphere(t_inter *inter, t_objs *sphere);

/* Utils */
t_objs	*get_node(t_objs *objs, int type);

/*			MATHS FOLDER			*/

/* Add Substract Maths */
t_vec	vec_substract(t_vec a, t_vec b);
t_vec	vec_substract_float(t_vec a, float b);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_add_float(t_vec vec, float nb);
float	vec_length(t_vec v);

/* Compare Maths */
bool	vec_compare(t_vec a, t_vec b);
t_vec	vec_max(t_vec v1, t_vec v2);
t_vec	vec_min(t_vec v1, t_vec v2);
float	ft_fabs(float f);
t_vec	vec_negate(t_vec v);

/* Dot Maths*/
float	dot_product(t_vec a, t_vec b);
float	dot_product_float(t_vec b, float a);
float	vec_pythagore(t_vec a);
t_vec	vec_cross(t_vec a, t_vec b);

/* Multiply Divide Maths */
t_vec	vec_multiply(t_vec a, t_vec b);
t_vec	vec_multiply_float(t_vec a, float f);
t_vec	vec_divide(t_vec a, float f);
float	vec_divide_float(t_vec a, float f);

/* Norm Maths */
float	get_norm(t_vec vec);
t_vec	vec_normalize(t_vec v);

/* Sqrt Maths */
t_vec	vec_squared(t_vec a);
t_vec	vec_sqrt(t_vec a);

#endif
