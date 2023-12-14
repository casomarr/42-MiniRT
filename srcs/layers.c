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
            img_pix_put(data, j++, i, color);
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
			img_pix_put(data, j++, i, color);
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
    
	//data->img.tab = NULL;
	data->img.tab = malloc(WIN_HEIGHT * sizeof(int *)); //proteger +  free
	int	i = 0;
	while(i < WIN_HEIGHT)
		data->img.tab[i++] = malloc(WIN_WIDTH * sizeof(int)); //proteger +  free

	background(data, WHITE);
    rectangle(data, GREEN);
	sphere(data, RED);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    return (0);
}

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = data->img.bpp - 8;
	pixel = data->img.addr + (y * data->img.width + x * (data->img.bpp / 8)); //magie voudou demander a patou
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (data->img.endian != 0) //big endian
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else //litle endian
			*pixel++ = (color >> (data->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
	data->img.tab[y][x] = color;
	//printf("color : %d\n", color);
}

void	sphere(t_data *data, int color)
{
	int	offset_x;
	int	offset_y;
	int	x;
	int	y;
	int	radius; //sera dans struct obj
	
	offset_x = 100;
	offset_y = 100;
	radius = 100;
	y = 0;
	while (y < radius)
	{
		x = 0;
		while (x < radius)
		{
			if (y * y + x * x <= radius * radius) //if (intersection == true)
			{
				img_pix_put(data, offset_x + x, offset_y - y, color);
				img_pix_put(data, offset_x - x, offset_y + y, color);
				img_pix_put(data, offset_x - x, offset_y - y, color);
				img_pix_put(data, offset_x + x, offset_y + y, color);
			}
			x++;
		}
		y++;
	}
}