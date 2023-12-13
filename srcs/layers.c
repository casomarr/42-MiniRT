#include "minirt.h"

void	background(t_data *data, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < WIN_HEIGHT)
    {
        j = 0;
        while (j < WIN_WIDTH)
            img_pix_put(&data->img, j++, i, color);
        i++;
    }
}

int rectangle(t_data *data, int color)
{
	int	i;
	int j;

	i = 300;
	while (i < 500)
	{
		j = 300;
		while (j < 500)
			img_pix_put(&data->img, j++, i, color);
		i++;
	}
	return (0);
}

int	render(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT); //remplit ma structure img
	data->img.addr  = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.width,
								&data->img.endian);
	int	aspect_ratio = 16.0 / 9.0; //ajoute pour ray_generation
	data->img.height = data->img.width / aspect_ratio; //ajoute pour ray_generation
    background(data, WHITE);
    rectangle(data, GREEN);
	sphere(data, RED);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->width + x * (img->bpp / 8)); //magie voudou demander a patou
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

void	sphere(t_data *data, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	radius; //sera dans struct obj
	
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
				img_pix_put(&data->img, x + j, y - i, color);
				img_pix_put(&data->img, x - j, y + i, color);
				img_pix_put(&data->img, x - j, y - i, color);
				img_pix_put(&data->img, x + j, y + i, color);
			}
			j++;
		}
		i++;
	}
}