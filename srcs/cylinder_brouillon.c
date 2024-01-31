/* t_vec vec_rotate(t_vec vector, t_vec axis) {
	t_vec result;

	float cos_theta = cosf(axis.x);
	float sin_theta = sinf(axis.x);

	float x_rot = vector.x;
	float y_rot = cos_theta * vector.y - sin_theta * vector.z;
	float z_rot = sin_theta * vector.y + cos_theta * vector.z;

	result.x = x_rot;
	result.y = cosf(axis.y) * y_rot + sinf(axis.y) * z_rot;
	result.z = -sinf(axis.y) * y_rot + cosf(axis.y) * z_rot;

	return result;
}

t_vec vec_invert(t_vec vector) {
	t_vec result;

	result.x = -vector.x;
	result.y = -vector.y;
	result.z = -vector.z;

	return result;
}

void check_intersection_cylinder(t_objs *cylinder, t_ray *ray)
{
	t_vec calc;

	// Transform ray into cylinder's local space
	t_vec local_origin = vec_substract(ray->origin, cylinder->pos);
	t_vec local_direction = vec_rotate(ray->dir, vec_invert(cylinder->dir));

	// Cylinder axis is y-axis
	calc.x = powf(local_direction.x, 2) + powf(local_direction.z, 2);
	calc.y = 2 * (local_origin.x * local_direction.x + local_origin.z * local_direction.z);
	calc.z = powf(local_origin.x, 2) + powf(local_origin.z, 2) - powf(cylinder->diameter / 2, 2);

	// Solve quadratic equation for t
	ray->discriminant = calc.y * calc.y - 4 * calc.x * calc.z;

	if (ray->discriminant < 0)
		return;  // No intersection

	float t1 = (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x);
	float t2 = (-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x);

	if ((t1 > 0 && t2 > 0 && t1 < t2) || (t1 > 0 && t2 < 0))
		ray->t = (-calc.y - sqrtf(ray->discriminant)) / (2 * calc.x);
	else if (t2 > 0)
		ray->t = (-calc.y + sqrtf(ray->discriminant)) / (2 * calc.x);
}

void intersection_point_cylinder(bool *intersection, t_data *data, t_objs *cylinder, t_ray *camera_ray)
{
	// Check if intersection points are within cylinder height
	float y = camera_ray->origin.y + camera_ray->t * dot_product(camera_ray->dir, cylinder->dir);

	//printf("y = %f, cylinder height: %f\n", y, cylinder->height);
	if (camera_ray->discriminant >= 0 && y >= 0 && y <= cylinder->height)
	{
		// printf("cylinder intersection found\n");
		*intersection = true;  // Intersection within cylinder height
		t_vec intersection_point_local = vec_add(camera_ray->origin, vec_multiply_float(camera_ray->dir, camera_ray->t));
		// if ((powf(intersection_point_local.x, 2) + powf(intersection_point_local.z, 2)) <= powf(cylinder->diameter / 2, 2))
		// {
			//printf("cylinder intersection found\n");
			// Transform intersection point back to world space
			t_vec intersection_point_world = vec_add(vec_rotate(intersection_point_local, cylinder->dir), cylinder->pos);
			if (camera_ray->t > 0 && camera_ray->t < data->z_index) //camera_ray->t > 0 car sinon derriere camera
			{
				data->z_index = camera_ray->t;
				data->closest_intersection_point = intersection_point_world;
				data->closest_object = *cylinder;
			}
		// }
	}
} */









/* t_vec	get_vec_abc(t_vec v, t_vec w, t_vec h, t_objs *cylinder)
{
	t_vec	maths;

	maths.x = vec_substract(vec_squared(v), vec_squared(vec_multiply(v, h)));

	maths.y = vec_multiply_float(vec_substract(vec_multiply(v, w), vec_multiply(vec_multiply(v, h), vec_multiply(w, h))), 2.);
 
	maths.z = vec_substract_float(vec_substract(vec_multiply(w, w), vec_squared(vec_multiply(w, h))), powf(cylinder->diameter / 2, 2.));

	return (maths);
}

void intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	t_vec	v;
	t_vec	w;
	t_vec	h;
	t_vec	H;
	float	delta;
	float	t;

	v = inter->cam_ray.dir;
	w = vec_substract(inter->cam_ray.origin, cylinder->pos);
	H = vec_add(cylinder->pos, vec_multiply_float(cylinder->dir, cylinder->height));
	h = vec_substract(H, cylinder->pos);
	
	maths = get_vec_abc(v, w, h, cylinder);
	delta = powf(maths.y, 2) - 4 * maths.x * maths.z;
	
	if (delta > 0)
	{
		if ((-maths.y + sqrtf(delta)) / (2. * maths.x) < (-maths.y - sqrtf(delta)) / (2. * maths.x))
 			t = (-maths.y + sqrtf(delta)) / (2. * maths.x);
 		else
 			t = (-maths.y - sqrtf(delta)) / (2. * maths.x);
	}
	else if (delta == 0.)
		t = -maths.y / (2. * maths.x);

	if (delta >= 0 && t > 0. && t < inter->dist)
	{
		inter->dist = t;
		inter->obj = cylinder;
		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
		// inter->normal = vec_normalize(vec_substract(inter->point, Q));
	}
} */

// https://www.illusioncatalyst.com/notes_files/mathematics/line_cylinder_intersection.php



/* t_vec RotateByDir(t_vec dir_origin, t_vec dir_dest, t_vec p)
{
	t_vec r;

    r = vec_normalize(vec_product(dir_origin, p));
    return (vec_product(dir_dest, r));
} */

/* static t_vec	get_vec_abc(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	t_ray	ray;

	ray = inter->cam_ray;
	maths.x = powf(ray.dir.y, 2);
	maths.y = 2 * ray.origin.y * ray.dir.y;
	maths.z = powf(ray.origin.y, 2) - powf(cylinder->diameter / 2, 2);
	return (maths);
}

void intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
{
	t_vec	maths;
	float	delta;
	float	t;

	maths = get_vec_abc(inter, cylinder);

	delta = powf(maths.y, 2) - 4 * maths.x * maths.z;
	
	if (delta >= 0)
	{
 			float t1 = (-maths.y + sqrtf(delta)) / (2. * maths.x);
 			float t2 = (-maths.y - sqrtf(delta)) / (2. * maths.x);
			if (t1 < t2)
				t = t1;
			else
				t = t2;
	}
	if (t1 < 0 && t2 > 0)
		//intersection
	if (delta >= 0 && t > 0. && t<= cylinder->height && t < inter->dist)
	{
		inter->dist = t; //pas besoin de re rotater avant
		inter->obj = cylinder;
		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
		//besoin de re rotater avec RotateByDir
		inter->normal = RotateByDir(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t), cylinder->pos);
	}
} */






//version en cours
// t_vec vec_rotate(t_vec vector, t_vec axis) {
// 	t_vec result;

// 	float cos_theta = cosf(axis.x);
// 	float sin_theta = sinf(axis.x);

// 	float x_rot = vector.x;
// 	float y_rot = cos_theta * vector.y - sin_theta * vector.z;
// 	float z_rot = sin_theta * vector.y + cos_theta * vector.z;

// 	result.x = x_rot;
// 	result.y = cosf(axis.y) * y_rot + sinf(axis.y) * z_rot;
// 	result.z = -sinf(axis.y) * y_rot + cosf(axis.y) * z_rot;

// 	return result;
// }

// t_vec vec_invert(t_vec vector) {
// 	t_vec result;

// 	result.x = -vector.x;
// 	result.y = -vector.y;
// 	result.z = -vector.z;

// 	return result;
// }

// void intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
// {

// 	t_vec maths;
// 	float	t;
// 	float	delta;

// 	// Transform ray into cylinder's local space
// 	t_vec local_origin = vec_substract(inter->cam_ray.origin, cylinder->pos);
// 	t_vec local_direction = vec_rotate(inter->cam_ray.dir, vec_invert(cylinder->dir));


// /* 	t_ray	ray;
// 	ray = inter->cam_ray;
// 	maths.x = powf(ray.dir.y, 2);
// 	maths.y = 2 * ray.origin.y * ray.dir.y;
// 	maths.z = powf(ray.origin.y, 2) - powf(cylinder->diameter / 2, 2); */
// 	// Cylinder axis is y-axis
// 	maths.x = powf(local_direction.x, 2) + powf(local_direction.z, 2);
// 	maths.y = 2 * (local_origin.x * local_direction.x + local_origin.z * local_direction.z);
// 	maths.z = powf(local_origin.x, 2) + powf(local_origin.z, 2) - powf(cylinder->diameter / 2, 2);

// 	// Solve quadratic equation for t
// 	delta = maths.y * maths.y - 4 * maths.x * maths.z;

// 	if (delta < 0)
// 		return;  // No intersection

// 	t = 0.;
// 	float t1 = (-maths.y - sqrtf(delta)) / (2 * maths.x);
// 	float t2 = (-maths.y + sqrtf(delta)) / (2 * maths.x);

// 	if ((t1 > 0 && t2 > 0 && t1 < t2) || (t1 > 0 && t2 < 0))
// 		t = (-maths.y - sqrtf(delta)) / (2 * maths.x);
// 	else if (t2 > 0)
// 		t = (-maths.y + sqrtf(delta)) / (2 * maths.x);
// 	// Check if intersection points are within cylinder height
// 	float y = inter->cam_ray.origin.y + t * dot_product(inter->cam_ray.dir, cylinder->dir);

// 	//printf("y = %f, cylinder height: %f\n", y, cylinder->height);
// 	if (delta >= 0 && y >= 0 && y <= cylinder->height)
// 	{
// 		// printf("cylinder intersection found\n");
// 		t_vec intersection_point_local = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, inter->cam_ray.t));
// 		// if ((powf(intersection_point_local.x, 2) + powf(intersection_point_local.z, 2)) <= powf(cylinder->diameter / 2, 2))
// 		// {
// 			//printf("cylinder intersection found\n");
// 			// Transform intersection point back to world space
// 			t_vec intersection_point_world = vec_add(vec_rotate(intersection_point_local, cylinder->dir), cylinder->pos);
// 			if (t > 0 && t < inter->dist) //t > 0 car sinon derriere camera
// 			{
// 				inter->dist = t;
// 				inter->obj = cylinder;
// 				inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
// 				inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
// 				//inter->normal = RotateByDir(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t), cylinder->pos);
// 			}
// 		// }
// 	}
// }






























// t_vec RotateByDir(t_vec dir_origin, t_vec dir_dest, t_vec p)
// {
// 	t_vec r;

//     r = vec_normalize(vec_product(dir_origin, p));
//     return (vec_product(dir_dest, r));
// }

// static t_vec	get_vec_abc(t_inter *inter, t_objs *cylinder)
// {
// 	t_vec	maths;
// 	t_ray	ray;

// 	ray = inter->cam_ray;
// 	maths.x = powf(ray.dir.y, 2) + powf(ray.dir.z, 2);
// 	maths.y = 2 * (ray.dir.y * ray.origin.y + ray.dir.z * ray.origin.z);
// 	maths.z = powf(ray.origin.y, 2), + powf(ray.origin.z, 2) - powf(cylinder->diameter / 2, 2);
// 	return (maths);
// }

// void intersection_point_cylinder(t_inter *inter, t_objs *cylinder)
// {
// 	t_vec	maths;
// 	float	delta;
// 	float	t;
// 	t_ray	ray;
// 	float epsilon = 1.0e-5;

// 	ray = inter->cam_ray;

// 	maths = get_vec_abc(inter, cylinder);
// 	delta = maths.y * maths.y - 4. * maths.x * maths.z; // b2 - 4ac

// 	// if (delta < 0)
// 	// 	return ;  // No intersection
// 	if (powf(ray.origin.y, 2) + powf(ray.origin.z, 2) <= powf(cylinder->diameter / 2, 2))
// 	{
// 		printf("111\n");
// 		//on se trouve dans l'alignement du cylindre
// 		if (ray.dir.x > cylinder->height || (ray.dir.x > 0 && ray.dir.x < cylinder->height))
// 		{
// 			printf("222\n");
// 			//si on se trouve sur la hauteur du cylindre
// 			t = (cylinder->height - ray.origin.x) / ray.dir.x;
// 			inter->normal = create_vec(1, 0, 0);
// 		}
// 		if (ray.origin.x < 0 || (ray.origin.x > 0 && ray.origin.x < cylinder->height))
// 		{
// 			printf("333\n");
// 			//si on se trouve sur la basseur du cylindre
// 			if (ray.dir.x == 0) //a verifier
// 				t = 0;
// 			else
// 				t = (-ray.origin.x )/ ray.dir.x;
// 			inter->normal = create_vec(-1, 0, 0);
// 		}
// 	}
// 	if (delta >= 0) //cote du cylindre
// 	{ //verifir si t1 et t2 dans le bon ordre
// 		printf("444\n");
// 		if ((-maths.y + sqrtf(delta)) / (2. * maths.x) < (-maths.y - sqrtf(delta)) / (2. * maths.x) && (-maths.y + sqrtf(delta)) / (2. * maths.x) > epsilon)
// 			t = (-maths.y + sqrtf(delta)) / (2. * maths.x);
// 		else if ((-maths.y - sqrtf(delta)) / (2. * maths.x) < (-maths.y + sqrtf(delta)) / (2. * maths.x) && (-maths.y - sqrtf(delta)) / (2. * maths.x) < epsilon)
// 			t = (-maths.y - sqrtf(delta)) / (2. * maths.x);
// 		inter->normal = vec_normalize(vec_substract(inter->point, cylinder->pos));
// 	}

// 	if (delta >= 0 && t > 0. && t<= cylinder->height && t < inter->dist)
// 	{
// 		printf("555\n");
// 		inter->dist = t; //pas besoin de re rotater avant
// 		inter->obj = cylinder;
// 		inter->point = vec_add(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t));
// 		//besoin de re rotater avec RotateByDir
// 		//inter->normal = RotateByDir(inter->cam_ray.origin, vec_multiply_float(inter->cam_ray.dir, t), cylinder->pos);
// 	}
// }





// /*Function that completes the intersection structure's data in case
// the camera ray is found to intersect with the cylinder*/
// void intersection_point_cylinder(t_ray camera_ray, t_objs *cylinder, t_inter *intersection)
// {
// 	/*- the t_ray structure has a direction vector and an origin vector.
// 	  - the t_objs structure has a position vector, a direction vector, a height (float),
// 	  and a diameter (float).
// 	  - the t_inter function has a point vector (point where the intersection takes place),
// 	    a norm (float) (the norm of the ray), and a distance (distance from the ray origin
// 		where the intersection happens).*/

// 	/*We divide the cylinder into three objects : two planes and a tube.
// 	We then check if the camera_ray intersects with any of these three objects and
// 	keep in the intersection structure the intersection point that is closest to the 
// 	camera ray (if multiple)*/

// 	/* if camera_ray intersects with the upper or lower plane
// 	{
// 		if the intersection is inside the cylinder's perimeter (if the intersection
// 		does not happen outside of the cylinder's diameter)
// 		{
// 			fill in :
// 			intersection->distance =
// 			intersection->point = 
// 			intersection->norm = 
// 		}
// 	} */

// 	/* if camera_ray intersects with the tube
// 	{
// 		if the intersection is inside the cylinder's height
// 		{
// 			fill in :
// 			intersection->distance =
// 			intersection->point = 
// 			intersection->norm = 
// 		}
// 	} */
// }
