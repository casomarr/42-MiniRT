#include "minirt.h"


// struct s_ray
// {
// 	int	origin;
// 	int	direction;
// 	int	norm;
// 	int	color;
// } t_ray;


// /*dessine un grand pixel*/
// int render_tiles(t_data *data)
// {
// 	int	i;
// 	int j;
// 	int x;
// 	int y;
// 	int radius;
// 	double	pi;
// 	double	area;
// 	int	color;

// 	radius = 200;
// 	pi = 3.1415926535;
// 	area = pi * pow(radius, 2);
// 	x = 500;
// 	y = 500;
	
// /* 	i = 100;
// 	while (i < 300)
// 	{
// 		j = 100;
// 		while (j < 300)
// 			mlx_pixel_put(mlx_ptr, win_ptr, j++, i, 0x00FF0000);
// 		++i;
// 	} */
// 	i = 0;
// 	while (i < radius)
// 	{
// 		j = 0;
// 		while (j < radius)
// 		{
// 			if (i * i + j * j <= radius * radius) //if (intersection == true)
// 			{
// 				// sinus = longeur ligne
// 				// cosinus = hauteur ligne
// 				// on doit mettre des pixels de sinus/cosinus a 0.



// 				//on genere le rayon
				
// 				//on determine la couleur
// 				//color = ray->color * object->color;
// 				//on affiche le pixel (pas possible d'avoir les 4 de suite comme ca)
// 				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + j, y - i, 0x00FF0000);
// 				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x - j, y + i, 0x00FF0000);
// 				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x - j, y - i, 0x00FF0000);
// 				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + j, y + i, 0x00FF0000);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	render_background(t_img *img, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < WIN_HEIGHT)
    {
        j = 0;
        while (j < WIN_WIDTH)
        {
            img_pix_put(img, j++, i, color);
        }
        ++i;
    }
}

int render_rect(t_img *img, int colour)
{
	int	i;
	int j;

	i = 100;
	while (i < 100 + 100)
	{
		j = 100;
		while (j < 100 + 100)
			img_pix_put(img, j++, i, colour);
		++i;
	}
	return (0);
}

int	render(t_data *data)
{
    if (data->win_ptr == NULL)
        return (1);
    render_background(&data->img, WHITE);
    render_rect(&data->img, GREEN);
    render_rect(&data->img, RED);

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

    return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	//printf("pixel = %s\n", pixel);
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
	//printf("data->img.bpp = %d\n", data->img.bpp);
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
				img_pix_put(&data->img, x + j, y - i, BLACK);
				img_pix_put(&data->img, x - j, y + i, BLACK);
				img_pix_put(&data->img, x - j, y - i, BLACK);
				img_pix_put(&data->img, x + j, y + i, BLACK);
			}
			j++;
		}
		i++;
	}
	render(data);
}