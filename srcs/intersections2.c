#include "minirt.h"

/*Checks if the light source is reachable by a straight
line from the point of intersection. We thus iterate through
each object and compare if the distance from the intersection
point is higher than the distance from other intersection points
from other objects. If yes, it means other objects are closer
on that same vector so our pixel is in the shadow.*/
void check_intersection_light(t_data *data, /* t_objs *current_sphere,  */t_ray *light_ray)
{
	t_objs *light;
	t_objs *object;
	t_vec	new_intersection;
	t_ray	*new_light_ray;
	float initial_distance;
	float	new_distance;

	if (light_ray->discriminant >= 0) //pas necessaire je pense : intersection tjrs possible
	{
		// if (light_ray->t > 0)
		// {
			// printf("ICI 1\n");
		// 	exit(1);

			light = get_node(data->scene.objs, LIGHT);
			if (light == NULL)
			{
				//gerer ce cas et proteger tous les autres get_node
				return ;
			}
			// data->closest_intersection_point = vecAdd(light_ray->origin, vecMultiplyFloat(light_ray->direction, light_ray->t));
			initial_distance = vecMagnitude(vecSubstract(data->closest_intersection_point, light->position));
			
			object = data->scene.objs;
			data->light_distance = FLT_MAX;
			while(object)
			{
				// if (object != current_sphere)
				// {
				new_light_ray = light_ray; //necessaire? je pense que je peux modifier light_ray a chaque fois
				if (object->type == SPHERE)
				{
					check_intersection_sphere(object, new_light_ray); //modifie new_light_ray
					if (light_ray->t > 0) //si intersection sur le meme axe
					{
						new_intersection = vecAdd(new_light_ray->origin, vecMultiplyFloat(new_light_ray->direction, new_light_ray->t));
						new_distance = vecMagnitude(vecSubstract(new_intersection, light->position));
						// if (initial_distance != new_distance)
						// 	printf("initial_distance = %f, new_distance = %f\n", initial_distance, new_distance);
						if (new_distance < data->light_distance)
							data->light_distance = new_distance;
					}
					/* new_light_ray = light_ray;
					check_intersection_init(object, new_light_ray); //modifie new_light_ray
					printf("object->type = %d,%d,%d\n", object->type, object->type, object->type);
					new_intersection = vecAdd(new_light_ray->origin, vecMultiplyFloat(new_light_ray->direction, new_light_ray->t));
					new_distance = vecMagnitude(vecSubstract(new_intersection, light->position));
					// printf("initial_distance = %f, new_distance = %f\n", initial_distance, new_distance);
					if (new_distance < data->light_distance)
						data->light_distance = new_distance; */
				// }
				}
				object = object->next;
			}
			if (initial_distance == data->light_distance || data->light_distance == FLT_MAX)
			{
				data->direct_light = true;
				data->light_distance = initial_distance; //pour color
			}
		// }
	}
}

/*Checks if the current ray intersects with each of the objects
present in the scene. Every time an intersection occurs, 
data->z_index is updated to keep in memory what is the closest
object that intersects with the ray, so that our image doesn't show
the "hidden" objects.*/
bool	intersection(t_data *data)
{
	bool	intersection;
	t_objs	*object;

	object = data->scene.objs;
	intersection = false;
	data->z_index = FLT_MAX;
	data->closest_intersection_point = create_vec(0.0, 0.0, 0.0);
	while (object)
	{
		if (object->type == SPHERE)
		{
			//mettre toutes ces fonctions en static dans un fichier spheres.c
			check_intersection_sphere(object, &data->ray); //camera ray
			intersection_point_sphere(&intersection, data, object, &data->ray);
			// data->ray.norm = 0.0;
			// data->ray.discriminant = 0.0;
			// data->ray.t = 0.0;
		}
		// else if (object->type == CYLINDER)
		// 	cylinder_intersection(&intersection, data);
		else if (object->type == PLANE)
		{
			check_intersection_plan(object, &data->ray, data);
			intersection_point_plan(&intersection, data, object, &data->ray);
		}
		object = object->next;
	}
	return (intersection);
}

