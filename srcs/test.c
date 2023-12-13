#include "minirt.h"


// struct s_ray
// {
// 	int	origin;
// 	int	direction;
// 	int	norm;
// 	int	color;
// } t_ray;

void	render_background(t_data *data, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < WIN_HEIGHT)
    {
        j = 0;
        while (j < WIN_WIDTH)
            img_pix_put(&data->img, j++, i, color);
			//mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
        i++;
    }
}

int render_rect(t_data *data, int color)
{
	int	i;
	int j;

	i = 100;
	while (i < 100 + WIN_HEIGHT)
	{
		j = 100;
		while (j < 100 + WIN_WIDTH)
			img_pix_put(&data->img, j++, i, color);
			//mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color); //s'affiche mais pq on ecrit direct sur la fenetre. Du coup si je mets ca enelever mlx_pput_img_ti_window
		i++;
	}
	return (0);
}

int	render(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr  = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len,
								&data->img.endian);
    render_background(data, WHITE);
    render_rect(data, RED);
	//sleep(10000);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8)); //magie voudou demander a patou
	// if (pixel == NULL)
	// 	return ;
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	sphere_img(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	radius; //sera dans struct obj

	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT); //remplit ma structure img
	data->img.addr  = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len,
								&data->img.endian);
	x = 100;
	y = 100;
	radius = 100;
	i = 0;
	while (i < radius)
	{
		j = 0;
		while (j < radius)
		{
			if (i * i + j * j <= radius * radius) //if (intersection == true)
			{
				img_pix_put(&data->img, x + j, y - i, RED);
				img_pix_put(&data->img, x - j, y + i, RED);
				img_pix_put(&data->img, x - j, y - i, RED);
				img_pix_put(&data->img, x + j, y + i, RED);
			}
			else
			{
				img_pix_put(&data->img, x + j, y - i, WHITE);
				img_pix_put(&data->img, x - j, y + i, WHITE);
				img_pix_put(&data->img, x - j, y - i, WHITE);
				img_pix_put(&data->img, x + j, y + i, WHITE);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 100, 100);
}