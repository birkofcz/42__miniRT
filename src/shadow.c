/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:37:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/23 17:28:13 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	sphere_shadow(t_ray ray, t_sp *sphere)
{
	t_quadratic_solution	solution;

	solution = quadratic_sphere(sphere->center, sphere->diameter / 2, ray);
	if (solution.discriminant < 0)
		return (false);
	if (solution.t1 > EPSILON || solution.t2 > EPSILON)
		return (true);
	return (false);
}
/*
bool cylinder_shadow(t_ray ray, t_cy *cylinder)
{
	t_quadratic_solution solution;
	t_vec3 hit_point;
	double projection;
	double t_hit;

	quadratic_cylinder(cylinder, ray, &solution);
	if (solution.discriminant < 0)
		return (false);
	t_hit = INFINITY;
	if (solution.t1 > EPSILON)
	{
		hit_point = clash_point(&ray, solution.t1);
		t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
		projection = dot_product(hit_to_center, cylinder->normal);
		if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
			t_hit = solution.t1;
	}
	if (solution.t2 > EPSILON)
	{
		hit_point = clash_point(&ray, solution.t2);
		t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
		projection = dot_product(hit_to_center, cylinder->normal);
		if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
			t_hit = fmin(t_hit, solution.t2);
	}
	if (t_hit < INFINITY)
		return true;
	t_vec3 top_center = addition(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));
	double t_top = dot_product(substraction(top_center, ray.origin), cylinder->normal) / dot_product(ray.direction, cylinder->normal);
	t_vec3 top_intersection = clash_point(&ray, t_top);
	if (dot_product(substraction(top_intersection, top_center), substraction(top_intersection, top_center)) <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
		return true;

	return false;
}
*/

bool cylinder_shadow(t_ray ray, t_cy *cylinder)
{
    t_quadratic_solution solution;
    t_vec3 hit_point;
    double projection;
    double t_hit;

    quadratic_cylinder(cylinder, ray, &solution);
    if (solution.discriminant < 0)
        return false;
    t_hit = INFINITY;
    if (solution.t1 >= EPSILON)
    {
        hit_point = clash_point(&ray, solution.t1);
        t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
        projection = dot_product(hit_to_center, cylinder->normal);
        if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
            t_hit = solution.t1;
    }
    if (solution.t2 >= EPSILON)
    {
        hit_point = clash_point(&ray, solution.t2);
        t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
        projection = dot_product(hit_to_center, cylinder->normal);
        if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
            t_hit = fmin(t_hit, solution.t2);
    }
    if (t_hit < INFINITY)
        return true;

    // Check the top cap intersection for shadow
    t_vec3 top_center = addition(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));
    double t_top = dot_product(substraction(top_center, ray.origin), cylinder->normal) / dot_product(ray.direction, cylinder->normal);
    t_vec3 top_intersection = clash_point(&ray, t_top);

    // Check if the normal is negative
    if (dot_product(cylinder->normal, ray.direction) > 0)
    {
        if (t_top >= EPSILON && dot_product(substraction(top_intersection, top_center), substraction(top_intersection, top_center)) <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
            return true;
    }
    
    return false;
}

static bool	intersect_shadow(t_ray ray, t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(ray, obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_shadow(ray, obj->object));
	return (false);
}

/*
Casting a shadow ray from the point of intersection
toward the light source and checking
if the ray intersects with any objects in the scene
before it reaches the light. If an intersection is found,
it means the point is in shadow; otherwise, it's illuminated.
*/


bool	is_in_shadow(t_scene *scene, t_hitrecord *rec)
{
	t_vec3		ray_to_light;
	t_ray		shadow_ray;
	t_object	*tmp;

	ray_to_light = substraction(scene->light.lightpoint, rec->clash);
	shadow_ray.origin = rec->clash;
	shadow_ray.direction = normalize_vector(ray_to_light);
	tmp = scene->head_object;
	while (tmp)
	{
		if (tmp == rec->obj)
		{
			tmp = tmp->next;
			continue ;
		}
		if (intersect_shadow(shadow_ray, tmp))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}