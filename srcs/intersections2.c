#include "minirt.h"

/*Checks if the current camera ray intersects with each of the objects
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
			check_intersection_sphere(object, &data->ray);
			intersection_point_sphere(&intersection, data, object, &data->ray);
		}
		else if (object->type == PLANE)
		{
			check_intersection_plan(object, &data->ray, data);
			intersection_point_plan(&intersection, data, object, &data->ray);
		}
		else if (object->type == LIGHT) //temporaire
		{
			t_objs *light = get_node(data->scene.objs, LIGHT);
			light->diameter = 3.5;
			light->color.argb[0] = 0;
			light->color.argb[1] = 255;
			light->color.argb[2] = 255;
			check_intersection_sphere(object, &data->ray);
			intersection_point_sphere(&intersection, data, object, &data->ray);
		}
		// else if (object->type == CYLINDER)
		// 	cylinder_intersection(&intersection, data);
		object = object->next;
	}
	return (intersection);
}

