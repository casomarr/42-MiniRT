/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/14 15:45:26 by casomarr         ###   ########.fr       */
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


typedef struct s_vec{
    float x, y, z;
} t_vec;

typedef struct t_color{
    float r, g, b;
} t_color;

typedef struct s_img
{
	void	*mlx_img; //address that mlx_new_image returns
	char	*addr;
	int		bpp; /* bits per pixel */
	int		width; //avant line_len, change pour ray_generation
	int		height;
	int		endian;
	int		**tab;
}	t_img;

typedef struct s_ray
{
	t_vec	camera_center;
	t_vec	pixel_00_location;
	t_vec	direction;
	int	norm;
	int	color;
	float	pixel_delta_w;
	float	pixel_delta_h;
}	t_ray;

typedef struct s_obj
{
	int	type; //define :sphere, cylinder, plane
	int	nb;
	struct s_obj	*next;
	//etc
}	t_obj;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_ray	ray;
	t_obj	obj;
}	t_data;

void	start_parsing(int fd);
bool	check_not_empty(int fd);
bool	open_file(char *path);
int		parsing(char *file_name);

/*Main*/
int	initialisation(t_data *data);

/*Layers*/
void	sphere(t_data *data, int color);
void	img_pix_put(t_data *data, int x, int y, int color);
void	newimg_pix_put(t_img *img, int x, int y, int color);
int 	rectangle(t_data *data, int color);
int		render(t_data *data);
void	background(t_data *data, int color);

/*Ray Generation*/
// void	ray_init(t_data *data);
// void	ray_generation(t_data *data);

// /*Maths*/
// t_vec	vecSubstract(t_vec a, t_vec b);
// t_vec vecAdd(t_vec a, t_vec b);

// /*Intersection Maths*/
// void	spheres_intersection(bool *intersection, t_data *data);
// bool	objects_iteration(t_data *data, int x, int y);

// /*Checks*/
// bool	intersection(t_data *data, int j, int i);

// /*Color*/
// int determine_color(t_data *data, int x, int y);

#endif
