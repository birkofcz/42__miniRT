/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:17:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/23 15:27:50 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
	if (obj->type == SPHERE)
		return (hit_sphere(scene, rec, obj));
	else if (obj->type == PLANE)
		return (hit_plane(scene, rec, obj));
	else if (obj->type == CYLINDER)
		return (hit_cylinder(scene, rec, obj));
	return (false);
}

/*
Loop through each object in the list and check if the ray intersects
with it
*/
bool	hittable_list_hit(t_scene *scene, t_hitrecord *rec)
{
	t_hitrecord	tmp_rec;
	bool		hit_anything;

	hit_anything = false;
	scene->ray.t_max = INFINITY; 
	scene->ray.t_min = EPSILON;
	tmp_rec.clash_distance = scene->ray.t_max;
	while (scene->object)
	{
		if (hit(scene, &tmp_rec, scene->object))
		{
			hit_anything = true;
			scene->ray.t_max = tmp_rec.clash_distance;
			*rec = tmp_rec;
		}
		scene->object = scene->object->next;
	}
	scene->object = scene->head_object;
	if (hit_anything == true)
		apply_light(scene, rec);
	return (hit_anything);
}


// Calculates the point of intersetion of ray and object.
// Clash (intersection point along the ray) = Origin  + t * Direction
t_vec3	clash_point(t_ray *ray, double t)
{
	t_vec3	clash;

	clash = multiply(ray->direction, t);
	clash = addition(ray->origin, clash);
	return (clash);
}

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

/*
Adding 0.5 for single-sample center of pixel
*/
t_ray	calculate_ray(t_scene *scene, int x, int y)
{
	double	u;
	double	v;
	t_vec3	direction;

	u = (x + 0.5) / WIDTH;
	v = (HEIGHT - y - 0.5) / HEIGHT;
	direction = direction_vec_creation(scene, u, v);
	return (create_ray(scene->cam.viewp, direction));
}
