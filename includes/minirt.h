/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2024/02/07 17:39:57 by amugnier         ###   ########.fr       */
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

//effacer, juste pour tests
#include <sys/types.h>
#include <sys/wait.h>

# define MAX_OBJS 256
#define PI 3.14159265358979323846

/*Patou : si le sujet ne specifie pas de taille d'image on
peut faire une image petite pour augmenter les fps.*/
// # define WIN_HEIGHT 900
// # define WIN_WIDTH 1600

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

# define STOP 0
# define PARSING_ERROR 1

# define ESC_KEY 65307
# define KEY_M 109
# define KEY_R 114

# define EPSILON 1e-6

#define MAX_DIST_CAMERA	FLT_MAX

# define ERROR_MSG1 "Error\n\x1B[1m"
# define ERROR_MSG2 "\x1B[31merror:\x1B[0m\x1B[1m "


typedef struct s_vec
{
	float x;
	float y;
	float z;
}	t_vec;

typedef unsigned int t_uint32;
typedef unsigned char t_uint8;

typedef union	u_color //le changer à bgra
{
	t_uint32	full;
	t_uint8		bgra[4];
}	t_color;

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
	t_vec	dir;
	float	norm;

	int		color;
	float	discriminant;
	float	t;
	t_vec	point; //pour norme au lieu de 3 float a, b, c
	float	pixel_delta_w;
	float	pixel_delta_h;
}	t_ray;

/*
typedef struct s_cam
{
	short			type; //a check 0 = sphere, 1 = plan, 2 = cylinder 3 = camera 4 = ambiant 5 = light
	t_vec			pos; //12
	t_vec			dir; //12
	t_vec			rdir; //12
	t_vec			udir;//12
	int				fov; //4
}			t_cam;


[OBJ1]

[OBJ2][OBJ3][OBJ4]

typedef struct s_sphere
{
	short			type; //a check 0 = sphere, 1 = plan, 2 = cylinder 3 = camera 4 = ambiant 5 = light
	t_vec			pos; //all
	t_color			color;
	float			diameter; //sphere and cylinder
} t_sphere

t_objs *obj;
if (obj->type == SPHERE)
	sphere = (t_sphere*)obj;
if (obj->type == CAMERA)
	camera = (t_camera*)obj;
obj = obj->next;

typedef struct s_objs
{
	short			type; //a check 0 = sphere, 1 = plan, 2 = cylinder 3 = camera 4 = ambiant 5 = light
	t_vec			pos; //all
	t_vec			dir; //plan and cylinder
	struct s_objs	*next;
} t_objs;
*/

typedef struct s_objs
{
	short			type; //a check 0 = sphere, 1 = plan, 2 = cylinder 3 = camera 4 = ambiant 5 = light
	t_vec			pos; //all
	t_vec			dir; //plan and cylinder
	t_color			color;
	float			diameter; //sphere and cylinder
	float			height; //cylinder only
	int				fov; //camera only
	float			lightness; //ambiant and light
	struct s_objs	*next;
} t_objs;

typedef struct 	s_inter {
	t_ray	ray;
	t_vec	point;
	t_vec	normal;
	float	dist;
	t_objs	*obj;
}				t_inter;

typedef struct 	s_lightray
{
	t_vec	point;
	t_vec	dir;
	t_vec	normal;
	float	dist;
}				t_ligthray;

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
	t_vec		first_pixel;
	t_vec		pixel_delta_u;
	t_vec		pixel_delta_v;


	//modification pas d'antoine TODO: Vérifier que ça fait pas de la merde au parsing
	t_vec		rdir;
	t_vec		udir;
} t_scene;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_scene	scene;
	bool	render_ambiant;



	t_ray	ray;
	t_ray	light_ray;
	int		x;
	int		y;
	float	z_index;
	t_vec	closest_intersection_point;
	t_objs	closest_object;
	bool	direct_light;
	float	norm;
	float	light_intensity;
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
void	write_scene_ppm(t_data *data);
// int	change_ambiant_render(int keycode, t_data *data);
bool	check_ovf_int(char *value, t_scene *scene, size_t size);
bool	check_nb_params(char **value, t_data *data);
bool	check_nb_cam(t_data *data);
bool	set_camera(t_objs *camera, char **value, t_data *data);
bool	set_ambiant(t_objs *ambiant, char **value, t_data *data);
bool	set_light(t_objs *light, char **value, t_data *data);
bool	set_sphere(t_objs *sphere, char **value, t_data *data);
bool	set_cylinder(t_objs *cylinder, char **value, t_data *data);
bool	check_nb_light(t_data *data);
bool	check_nb_ambiant(t_data *data);


void	ft_stop(t_data *data, short error);


/*Main*/
int		initialisation(t_data *data);
int		esc_close(int keycode, t_data *data);
int		cross_close(t_data *data);
/*Rays*/
void	ray_init(t_data *data);
void	minirt(t_data *data);
void	normalize_direction_vector(t_ray *ray);
// void	generate_current_ray(t_data *data);
t_ray	compute_camera_ray(int x, int y, t_scene scene);
int		compute_pixel(int x, int y, t_data *data);
// void	compute_ray(t_data *data, float x, float y);
t_inter	compute_light_ray(t_inter inter, t_objs *light, t_objs *objects);
void	distance_of_projection(t_data *data);

/*Vector Maths*/
t_vec	create_vec(float x, float y, float z);
t_vec	vec_substract(t_vec a, t_vec b);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_multiply(t_vec a, t_vec b);
t_vec	vec_squared(t_vec a);
t_vec	vec_sqrt(t_vec a);
float	dot_product(t_vec a, t_vec b);
float	dot_product_float(t_vec b, float a);
t_vec	vec_multiply_float(t_vec a, float f);
float	vec_pythagore(t_vec a);
t_vec	vec_add_float(t_vec vec, float nb);
t_vec	vec_divide(t_vec a, float f);
t_vec	vec_product(t_vec a, t_vec b);
t_vec	vec_substract_float(t_vec a, float b);
float	vec_divide_float(t_vec a, float f);
t_vec	vec_divide(t_vec a, float f);
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_max(t_vec v1, t_vec v2);
t_vec	vec_min(t_vec v1, t_vec v2);
t_vec	vec_clamp(t_vec v, float min, float max);
float	get_norm(t_vec vec);
bool	vec_compare(t_vec a, t_vec b);
t_vec vec_normalize(t_vec v);
float	ft_fabs(float f);

/*Intersections*/
void	check_intersection_sphere(t_objs *sphere, t_ray *ray);
void	intersection_point_sphere(t_inter *inter, t_objs *sphere);
void	check_intersection_light(t_data *data, /* t_objs *current_sphere,  */t_ray *light_ray);
t_inter	closest_intersection(t_ray ray, t_objs *object, float dist);
float	get_norm(t_vec vec);
t_vec	get_intersection_point_sphere(t_objs *sphere, t_ray *ray, t_data *data);
float	ft_fabs(float f);

/*Color*/
int		get_color(unsigned char color, float light_intensity);
float	determine_pixel_color(t_data *data);
t_color	color_from_rgb(t_uint8 r, t_uint8 g, t_uint8 b);
t_color	color_from_vec(t_vec v);
int	get_pixel_color(t_inter inter, t_objs *objects, t_data *data, t_ray ray);

/*Cylinder*/
// void	check_intersection_cylinder(t_objs *cylinder, t_ray *ray);
// void	intersection_point_cylinder(bool *intersection, t_data *data, t_objs *cylinder, t_ray *camera_ray);
void intersection_point_cylinder(t_inter *inter, t_objs *cylinder);

/*Render*/
void	img_pix_put(t_data *data, int x, int y, int color);
// void	add_pixel_to_img(t_data *data, int color);

/*Light Intensity*/
float	clamp(float value, float min, float max);
float	lerp(float ratio, float min, float max);
float	brdf(t_data *data);
float	bouncing(t_data *data);

/*Utils*/
t_objs	*get_node(t_objs *objs, int type);

/*Plane intersection*/
void	get_norm2(t_vec *a, t_data *data);
void	check_intersection_plane(t_objs *object, t_ray *ray, t_data *data);
// void	intersection_point_plane(bool *intersection, t_data *data, t_objs *object, t_ray *ray);
void	intersection_point_plane(t_inter *inter, t_objs *plane);
t_vec	get_intersection_point_plane(t_data *data, t_objs *object, t_ray *ray);
t_vec	vec_normalize(t_vec v);

/*Lightray*/
t_vec	get_ambi_rgb(t_inter inter, t_objs *ambient, t_data *data, t_ray ray);
t_vec	get_light_rgb(t_inter inter, t_objs *light, t_objs *objs, t_inter *interlight);

#endif
