#include "minirt.h"

void check_intersection_init(t_objs *object, t_ray *ray)
{
	ray->point.x = DotProduct(ray->direction, ray->direction);
	ray->point.y = 2 * DotProduct(ray->direction, vecSubstract(ray->origin, object->position));
	ray->point.z = DotProduct(vecSubstract(ray->origin, object->position), vecSubstract(ray->origin, object->position)) - powf(object->diameter, 2);
	ray->discriminant = powf(ray->point.y, 2) - (4 * ray->point.x * ray->point.z);
	if (ray->discriminant >= 0)
	{
		if ((-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x) < (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x))
			ray->t = (-ray->point.y + sqrtf(ray->discriminant)) / (2 * ray->point.x);
		else
			ray->t = (-ray->point.y - sqrtf(ray->discriminant)) / (2 * ray->point.x);
	}
}

void check_intersection_camera(bool *intersection, t_data *data, t_objs *object, t_ray *ray)
{
	if (ray->discriminant >= 0)
	{
		*intersection = true;
		if (ray->t > 0)
		{
			data->intersection_point = vecAdd(data->ray.origin, vecMultiplyFloat(data->ray.direction, ray->t));
			if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
			{
				// printf("z_index updated\n");
				data->z_index = ray->t; // et non data->intersection_point.z car peut etre négatif vu que 3D
				data->closest_intersection_point = data->intersection_point;
				data->closest_object_type = object->type;
				data->front_object_color = object->color.full;
			}
		}
	}
}

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
			// data->closest_intersection_point = vecAdd(light_ray->origin, vecMultiplyFloat(light_ray->direction, light_ray->t));
			initial_distance = vecMagnitude(vecSubstract(data->closest_intersection_point, light->position));
			
			object = data->scene.objs;
			data->light_distance = FLT_MAX;
			// printf("1er object list AVANT WHILE: type = %d\n", data->scene.objs->type);
			while(object)
			{
				// if (object != current_sphere)
				// {
				new_light_ray = light_ray; //necessaire? je pense que je peux modifier light_ray a chaque fois
				if (object->type == SPHERE)
				{
					check_intersection_init(object, new_light_ray); //modifie new_light_ray
					if (light_ray->t > 0) //si intersection sur le meme axe
					{
						new_intersection = vecAdd(new_light_ray->origin, vecMultiplyFloat(new_light_ray->direction, new_light_ray->t));
						new_distance = vecMagnitude(vecSubstract(new_intersection, light->position));
						if (initial_distance != new_distance)
							printf("initial_distance = %f, new_distance = %f\n", initial_distance, new_distance);
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
			// printf("1er object list APRES WHILE: type = %d\n", data->scene.objs->type);
			// exit(1);
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
	while (object)
	{
		if (object->type == SPHERE)
		{
			//mettre toutes ces fonctions en static dans un fichier spheres.c
			check_intersection_init(object, &data->ray); //camera ray
			check_intersection_camera(&intersection, data, object, &data->ray);
		}
		/* else if (object->type == CYLINDER)
			cylinder_intersection(&intersection, data);
		else if (object->type == PLANE)
			plane_intersection(&intersection, data); */
		object = object->next;
	}
	return (intersection);
}
