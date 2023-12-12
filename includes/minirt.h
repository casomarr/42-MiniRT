/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:33:36 by amugnier          #+#    #+#             */
/*   Updated: 2023/12/12 18:58:52 by casomarr         ###   ########.fr       */
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

# define WHITE 0x00FFFFFF
# define BLACK 0x00FF0000
# define RED 0x0000FF00
# define GREEN 0x0000FF00

typedef struct s_img
{
	void	*mlx_img; //address that mlx_new_image returns
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

void	start_parsing(int fd);
bool	check_not_empty(int fd);
bool	open_file(char *path);
int		parsing(char *file_name);

int		render_tiles(t_data *data);
void	sphere_img(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
int render_rect(t_img *img, int colour);
int	render(t_data *data);
void	render_background(t_img *img, int color);

#endif
