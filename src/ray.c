/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:17:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/18 20:00:39 by tkajanek         ###   ########.fr       */
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

bool hittable_list_hit(t_scene *scene, t_hitrecord *rec)
{
    t_hitrecord tmp_rec;
    bool hit_anything;

    hit_anything = false;
	scene->ray.t_max = INFINITY; 
    scene->ray.t_min = EPSILON;
    tmp_rec.clash_distance = scene->ray.t_max; //INFINITY

    // Loop through each object in the list

    while (scene->object)
    {
		
        // Check if the ray intersects with the current object
        if (hit(scene, &tmp_rec, scene->object))
        {
            hit_anything = true;
            scene->ray.t_max = tmp_rec.clash_distance;
            *rec = tmp_rec;  // Update the hit record with the temporary hit record
        }
        scene->object = scene->object->next;  // Move to the next object in the list
    }
    scene->object = scene->head_object;  // Reset the object pointer to the beginning

    // If there was a hit, apply lighting and shading calculations
	if (hit_anything == true)
		apply_light(scene, rec);

    return (hit_anything);  // Return whether any object was hit
}


t_rgb	ray_color2(t_scene *scene)
{
	t_hitrecord	rec;

	if (hittable_list_hit(scene, &rec))
		return (rec.color);
	//return (fill_color(0, 0, 0));
	/*t_vec3 unit_direction = normalize_vector(scene->ray.direction);
    double t = 0.5 * (unit_direction.y + 1.0);

    t_rgb white = {255, 255, 255};
    t_rgb blue = {255*0.5, 255*0.7, 255};
    t_rgb c1, c2, result;
    c1.r = (1.0 - t) * white.r;
    c1.g = (1.0 - t) * white.g;
    c1.b = (1.0 - t) * white.b;

    c2.r = t * blue.r;
    c2.g = t * blue.g;
    c2.b = t * blue.b;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;*/
	t_rgb result;
	result.r = 0;
    result.g = 0;
    result.b = 0;

    return (result);
}	

/*
t_rgb	ray_color(t_ray ray, t_scene *scene)
{

    if (hit_sphere(scene->sp[0].center, scene->sp[0].diameter / 2, ray))
		return (scene->sp[0].color);

    t_vec3 unit_direction = normalize_vector(ray.direction);
    double t = 0.5 * (unit_direction.y + 1.0);

    t_rgb white = {255, 255, 255};
    t_rgb blue = {255*0.5, 255*0.7, 255};
    t_rgb c1, c2, result;
    c1.r = (1.0 - t) * white.r;
    c1.g = (1.0 - t) * white.g;
    c1.b = (1.0 - t) * white.b;

    c2.r = t * blue.r;
    c2.g = t * blue.g;
    c2.b = t * blue.b;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;

    return result;
}*/

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
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

