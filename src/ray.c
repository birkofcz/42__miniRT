/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:17:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/21 14:57:01 by tkajanek         ###   ########.fr       */
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


t_rgb	ray_color(t_scene *scene)
{
	t_hitrecord	rec;

	if (hittable_list_hit(scene, &rec))
		return (rec.color);
	//return (fill_rgb(0, 0, 0));
	t_rgb result;
	result.r = 0;
    result.g = 0;
    result.b = 0;

    return (result);
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
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}



static t_vec3	direction_vec_creation(t_scene *scene, double u, double v)
{
	t_vec3 horizontal_contribution;
	t_vec3 vertical_contribution;
	t_vec3 horizontal_sum;
	t_vec3 horizontal_and_vertical_sum;

	horizontal_contribution = multiply(scene->cam.horizontal, u);
	vertical_contribution = multiply(scene->cam.vertical, v);
	horizontal_sum = addition(scene->cam.lower_left_corner, horizontal_contribution);
	horizontal_and_vertical_sum = addition(horizontal_sum, vertical_contribution);
	return(substraction(horizontal_and_vertical_sum, scene->cam.viewpoint));
}

/*
Adding 0.5 for single-sample center of pixel
*/
t_ray	calculate_ray(t_scene *scene, int x, int y)
{

    double u;
	double v;
	t_vec3	direction;

 	u = (x + 0.5) / WIDTH;     
    v = (HEIGHT - y - 0.5) / HEIGHT; 
	direction = direction_vec_creation(scene, u, v);
	return(create_ray(scene->cam.viewpoint, direction));
}
