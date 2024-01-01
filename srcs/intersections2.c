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
			// data->intersection_point = vecAdd(data->ray.origin, vecMultiplyFloat(data->ray.direction, ray->t));
			if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
			{
				// printf("z_index updated\n");
				data->z_index = ray->t; // et non data->intersection_point.z car peut etre négatif vu que 3D
				data->front_object_color = object->color.full;
			}
		}
	}
}

/*Checks if the light source is reachable by a straight
line from the point of intersection. If not, it means the
current pixel is in the shadow.*/
void check_intersection_light(t_data *data, t_ray *ray)
{

/* 	if (ray->discriminant >= 0)
	{
		if (distance_light_object(data) < ray->norm)
		// if (ray->norm < distance_light_object(data)) //ne change rien dans un sens ou dans l'autre... alors quw devrait
			data->direct_light = true;
	} */


/* 	if (ray->discriminant >= 0)
	{
		if (ray->t > 0 && ray->t < data->z_index) //ray->t > 0 car sinon derriere camera
			data->direct_light = true;
	} */


	t_objs *light;
	float distance_to_light;

	if (ray->discriminant >= 0)
	{
		if (ray->t > 0)
		{
			light = get_node(data->scene.objs, LIGHT);
			data->intersection_point = vecAdd(data->ray.origin, vecMultiplyFloat(data->ray.direction, ray->t));
			distance_to_light = vecMagnitude(vecSubstract(data->intersection_point, light->position));
			if (distance_to_light < ray->norm)
				data->direct_light = true;
		}
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
	data->direct_light = false;
	// data->z_index = FLT_MAX; //ne marche pas à la maison
	data->z_index = 100000; //`à 42 mettre FLT_MAX
	while (object)
	{
		if (object->type == SPHERE)
		{
			//mettre toutes ces fonctions en static dans un fichier spheres.c
			check_intersection_init(object, &data->ray); //camera ray
			check_intersection_camera(&intersection, data, object, &data->ray);
			generate_light_ray(data);
			check_intersection_init(object, &data->ray); //light ray
			check_intersection_light(data, &data->ray);
		}
		/* else if (object->type == CYLINDER)
			cylinder_intersection(&intersection, data);
		else if (object->type == PLANE)
			plane_intersection(&intersection, data); */
		object = object->next;
	}
	// printf("intersection = %d\n", intersection); //0 = false
	return (intersection);
}
