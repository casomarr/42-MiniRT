/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_maths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:47:22 by casomarr          #+#    #+#             */
/*   Updated: 2023/12/14 15:07:31 by casomarr         ###   ########.fr       */
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

// void	spheres_intersection(bool *ret, t_data *data)
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




void	spheres_intersection(bool *intersection, t_data *data)
{
	t_vec	ray_location;
	t_vec	tmp;

	ray_location = vecSubstract(data->ray.direction, 2 * data->ray.norm);
	tmp = vecProduct(data->ray.direction, data->ray.norm);
	ray_location = vecProduct(ray_location, tmp);

	if (compare(ray_location, data->img.??) == true) /*envoyer mlx_img 
	et comme void * je peux faire [x][y]? dans ce cas utiliser le x et 
	le y de intersection(). NON il me faut un t_vec dans img*/
		intersection = true;
}

bool	objects_iteration(t_data *data, int x, int y)
{
/*fonction avec une while qui parcours a chaque fois qu'elle est appellee toute
 la liste d'objets presents dans la scene pour modifier ou pas la valeur de ret 
 en fonction. If ret == false et que now true on met ret a true. Par contre si 
 ret etait deja a true et que now false on ne modifie pas sa valeur (true prime).*/
	bool	intersection;

	intersection = false;
	while (data->obj)
	{
		if (data->obj->type == SPHERE)
			sphere_intersection(&intersection, data);
		else if (data->obj->type == CYLINDER)
			cylinder_intersection(&intersection, data);
		else if (data->obj->type == PLANE)
			plane_intersection(&intersection, data);
		data->obj = data->obj->next;
	}
	return (intersection);
}