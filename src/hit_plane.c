/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:29:34 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/14 18:50:07 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
if denominator is == 0, the plane is parallel to the ray.
if it's positive, indicating that the ray is facing away from the plane.
 A positive dot product between the normal vector and the direction vector
 means that the angle between them is greater than 90 degrees,
 and thus the ray is not intersecting the front side of the plane.
*/

bool	hit_plane(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
	double	denominator;
	t_pl	*plane;
	t_vec3	point_to_origin;

	plane = obj->object;
	write(1,"test1\n", 7);
	//plane->normal = normalize_vector(plane->normal);
	denominator = dot_product(plane->normal, scene->ray.direction);
	if (fabs(denominator) < EPSILON || denominator > 0)
		return (false);
	point_to_origin = substraction(plane->point, scene->ray.origin);
	rec->clash_distance = dot_product(point_to_origin, plane->normal) / denominator;
	if (rec->clash_distance < scene->ray.t_min
		|| rec->clash_distance > scene->ray.t_max)
		return (false);
	rec->clash = clash_point(&scene->ray, rec->clash_distance);
	rec->type = PLANE;
	rec->normal = plane->normal;
	rec->color = plane->color;
	rec->obj = obj;
	return (true);
}