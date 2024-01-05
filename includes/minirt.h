/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/01/05 20:55:24 by casomarr         ###   ########.fr       */
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


#include <sys/types.h>
#include <sys/wait.h>


# define MAX_OBJS 256

/*Patou : si le sujet ne specifie pas de taille d'image on
peut faire une image petite pour augmenter les fps.*/
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define SPHERE		0
# define CYLINDER	1
# define PLANE		2
# define CAMERA		3
# define AMBIENT	4
# define LIGHT		5

# define ESC_KEY 65307

typedef struct s_vec
{
	float x;
	float y;
	float z;
}	t_vec;

typedef unsigned int t_uint32;
typedef unsigned char t_uint8;

typedef union	u_rgb
{
	t_uint32	full;
	t_uint8		argb[4];
}	t_rgb;

typedef struct s_img
{
	void	*mlx_img; //address that mlx_new_image returns
	char	*addr;
	int		bpp; /* bits per pixel */
	int		width; //avant line_len, change pour ray_generation
	int		height;
	int		endian;
}	t_img;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	current_pixel;
	t_vec	location;
	t_vec	direction;
	float	norm;
	int		color;
	float	discriminant;
	float	t;
	t_vec	point; //pour norme au lieu de 3 float a, b, c
	float	pixel_delta_w;
	float	pixel_delta_h;
}	t_ray;

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
	int		x;
	int		y;
	float	z_index;
	float	light_distance;
	int		front_object_color;
	t_vec	intersection_point;
	t_vec	closest_intersection_point;
	int		closest_object_type;
	t_objs	current_object;
	bool	direct_light;
	float	distance_of_projection;
	t_vec	current_pixel;
}	t_data;

/* typedef struct s_check_objs
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
t_objs	*lst_new_objs(void); */

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
bool	check_lightness(t_objs *objs);
bool	check_color(t_objs *objs);
bool	check_vector(t_objs *objs);
bool	check_fov(t_objs *objs);
bool	check_height(t_objs *objs);
bool	check_data_objs(t_objs *objs);
bool	check_diameter(t_objs *objs);
bool	check_coords(t_objs *objs);

/*Main*/
int		initialisation(t_data *data);

/*Rays*/
void	ray_init(t_data *data);
void	ray_generation(t_data *data);
void	get_norm(t_ray *ray);
void	normalize_direction_vector(t_ray *ray);
// void	generate_current_ray(t_data *data);
void	generate_camera_ray(t_data *data);
void	generate_light_ray(t_data *data);
void	distance_of_projection(t_data *data);

/*Vector Maths*/
t_vec	create_vec(float x, float y, float z);
t_vec	vecSubstract(t_vec a, t_vec b);
t_vec	vecAdd(t_vec a, t_vec b);
t_vec	vecMultiply(t_vec a, t_vec b);
t_vec	vecSquared(t_vec a);
t_vec	vecSqrt(t_vec a);
float	DotProduct(t_vec a, t_vec b);
t_vec	vecMultiplyFloat(t_vec a, float f);
float	vecMagnitude(t_vec a);

/*Intersections*/
// void	camera_sphere_intersection(bool *intersection, t_data *data, t_objs *sphere);
// void	sphere_light_intersection(t_data *data, t_objs *object);
void check_intersection_init(t_objs *object, t_ray *ray);
void check_intersection_camera(bool *intersection, t_data *data, t_objs *object, t_ray *ray);
void check_intersection_light(t_data *data, /* t_objs *current_sphere,  */t_ray *light_ray);
bool	intersection(t_data *data);

/*Color*/
int		get_color(unsigned char color, float light_intensity);
float		determine_pixel_color(t_data *data);
// void	determine_pixel(t_data *data);

/*Render*/
void	img_pix_put(t_data *data, int x, int y, int color);
// void	add_pixel_to_img(t_data *data, int color);

/*Light Intensity*/
bool	direct_light(t_data *data);
float	distance_light_object(t_data *data);
float		brdf(t_data *data);
float		shadows(t_data *data);

/*Utils*/
t_objs	*get_node(t_objs *objs, int type);

#endif
