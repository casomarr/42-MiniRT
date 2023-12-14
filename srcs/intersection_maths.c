/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_maths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:47:22 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/14 18:20:33 by casomarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void objects_iteration(bool *ret, bool (*ft)(t_ray *ray), t_ray *objects, t_img *tab)
// {
// /*fonction avec une while qui parcours a chaque fois qu'elle est appellee toute
//  la liste d'objets presents dans la scene pour modifier ou pas la valeur de ret 
//  en fonction. If ret == false et que now true on met ret a true. Par contre si 
//  ret etait deja a true et que now false on ne modifie pas sa valeur (true prime).*/
// 		while (objects)
// 		{
// 				if ((*ft)(ray) == true) //si intersection avec cet objet (si fonction envoyee en params = true)
// 						ret = true;
// 				objects = objects->next;
// 		}
// }

// void	sphere_intersection(bool *ret, t_data *data)
// {
// 	t_vec	ray_location;

// 	ray_location = data->ray.direction - 2 * data->ray.norm * \
// 	dotProduct(data->ray.direction, data->ray.norm);

// 	if (compare(ray_location, data->img.??) == true) /*envoyer mlx_img 
// 	et comme void * je peux faire [x][y]? dans ce cas utiliser le x et 
// 	le y de intersection()*/
// 		ret = true;
// }

// bool	objects_iteration(bool *ret, t_data *data, int x, int y)
// {
// /*fonction avec une while qui parcours a chaque fois qu'elle est appellee toute
//  la liste d'objets presents dans la scene pour modifier ou pas la valeur de ret 
//  en fonction. If ret == false et que now true on met ret a true. Par contre si 
//  ret etait deja a true et que now false on ne modifie pas sa valeur (true prime).*/
// 	while (data->obj)
// 	{
// 		if (data->obj->type == SPHERE)
// 			sphere_intersection(ret, data);
// 		else if (data->obj->type == CYLINDER)
// 			cylinder_intersection(ret, data);
// 		else if (data->obj->type == PLANE)
// 			plane_intersection(ret, data);
// 		data->obj = data->obj->next;
// 	}
// }



void	sphere_intersection(bool *intersection, t_data *data)
{
/* 	t_vec	ray_location;
	t_vec	tmp_calc;
	
	//ray_location = vecSubstract(data->ray.direction, 2 * data->ray.norm);
	ray_location.x = data->ray.direction.x - (2 * data->ray.norm);
	ray_location.y = data->ray.direction.y - (2 * data->ray.norm);
	ray_location.z = data->ray.direction.z - (2 * data->ray.norm);
	
	// tmp_calc = vecProduct(data->ray.direction, data->ray.norm);
	tmp_calc.x = data->ray.direction.x * data->ray.norm;
	tmp_calc.y = data->ray.direction.y * data->ray.norm;
	tmp_calc.z = data->ray.direction.z * data->ray.norm; 
	
	ray_location = vecProduct(ray_location, tmp_calc);

	int tmp;
	int x;
	int y;

	tmp = ray_location.x + WIN_WIDTH * ray_location.y;
	x = tmp % WIN_WIDTH;
	y = tmp / WIN_WIDTH;

	while (tmp < WIN_WIDTH * WIN_HEIGHT)
	{
		tmp++;
		x = tmp % WIN_WIDTH;
		y = tmp / WIN_WIDTH;
		printf("on est sur le pixel %d:%d qui est de couleur %d\n", x, y, data->img.tab[y][x]);
	}

	if (data->img.tab[y][x] != WHITE) //WHITE = BACKGROUND COLOR
		*intersection = true; */



/* 	t_vec ray_location;
    t_vec tmp_calc;
    
    // Calculate ray location
    ray_location.x = data->ray.camera_center.x + data->ray.direction.x * data->ray.norm;
    ray_location.y = data->ray.camera_center.y + data->ray.direction.y * data->ray.norm;
    ray_location.z = data->ray.camera_center.z + data->ray.direction.z * data->ray.norm;

    // Calculate tmp_calc using the normalized ray direction
    tmp_calc.x = data->ray.direction.x;
    tmp_calc.y = data->ray.direction.y;
    tmp_calc.z = data->ray.direction.z;
    
    ray_location = vecAdd(ray_location, tmp_calc); // You should use vecSum instead of vecProduct here

    int x = (int)(ray_location.x * WIN_WIDTH);
    int y = (int)(ray_location.y * WIN_HEIGHT);

    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
        printf("Intersection at pixel %d:%d, color %d\n", x, y, data->img.tab[y][x]);

        if (data->img.tab[y][x] != WHITE) // WHITE = BACKGROUND COLOR
            *intersection = true;
    } */

	

	t_vec ray_location;

    // Calculate ray location
    ray_location.x = data->ray.camera_center.x + data->ray.direction.x * data->ray.norm;
    ray_location.y = data->ray.camera_center.y + data->ray.direction.y * data->ray.norm;
    ray_location.z = data->ray.camera_center.z + data->ray.direction.z * data->ray.norm;

    int x = (int)(ray_location.x * WIN_WIDTH);
    int y = (int)(ray_location.y * WIN_HEIGHT);

    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
		//n'arrive jamais ICI
        printf("Intersection at pixel %d:%d\n", x, y);

        if (data->img.tab[y][x] != WHITE) // WHITE = BACKGROUND COLOR
		{
			printf("INTERSECTION = TRUE\n");
            *intersection = true;
		}
    }
}

bool	objects_iteration(t_data *data)
{
/*fonction avec une while qui parcours a chaque fois qu'elle est appellee toute
 la liste d'objets presents dans la scene pour modifier ou pas la valeur de ret 
 en fonction. If ret == false et que now true on met ret a true. Par contre si 
 ret etait deja a true et que now false on ne modifie pas sa valeur (true prime).*/
	bool	intersection;
	t_obj	*objects;

	objects = &data->obj;
	intersection = false;
	while (objects)
	{
		if (objects->type == SPHERE)
			sphere_intersection(&intersection, data);
		/* else if (objects->type == CYLINDER)
			cylinder_intersection(&intersection, data);
		else if (objects->type == PLANE)
			plane_intersection(&intersection, data); */
		objects = objects->next;
	}
	printf("intersection = %d\n", intersection); //false = 0
	return (intersection);
}