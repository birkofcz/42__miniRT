/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:37:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/24 14:37:49 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"


/* bool	cylinder_shadow(t_ray ray, t_cy *cylinder)
{
	t_quads	solution;
	t_vec3	hit_point;
	double	projec;
	double	t_hit;
	t_vec3	hit_to_center;

	quadratic_cylinder(cylinder, ray, &solution);
	if (solution.discriminant < 0)
		return (false);
	t_hit = INFINITY;
	if (solution.t1 >= EPSILON)
	{
		hit_point = clash_point(&ray, solution.t1);
		hit_to_center = substraction(hit_point, cylinder->center);
		projec = dot_product(hit_to_center, cylinder->normal);
		if (projec >= -cylinder->height / 2 && projec <= cylinder->height / 2)
			t_hit = solution.t1;
	}
	if (solution.t2 >= EPSILON)
	{
		hit_point = clash_point(&ray, solution.t2);
		hit_to_center = substraction(hit_point, cylinder->center);
		projec = dot_product(hit_to_center, cylinder->normal);
		if (projec >= -cylinder->height / 2 && projec <= cylinder->height / 2)
			t_hit = fmin(t_hit, solution.t2);
	}
	if (t_hit < INFINITY)
		return true;
	t_vec3 top_center = addition(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));
	double t_top = dot_product(substraction(top_center, ray.origin), cylinder->normal) / dot_product(ray.direction, cylinder->normal);
	t_vec3 top_intersection = clash_point(&ray, t_top);
	if (dot_product(substraction(top_intersection, top_center), substraction(top_intersection, top_center)) <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
		return (true);
	return (false);
} */

bool	check_solution(t_ray *ray, t_cy *cylinder, double t, double *t_hit)
{
	t_vec3	hit_point;
	t_vec3	hit_to_center;
	double	projec;

	hit_point = clash_point(ray, t);
	hit_to_center = substraction(hit_point, cylinder->center);
	projec = dot_product(hit_to_center, cylinder->normal);
	if (projec >= -cylinder->height / 2 && projec <= cylinder->height / 2) 
	{
		*t_hit = fmin(*t_hit, t);
		return (true);
	}
	return (false);
}

bool	check_top_intersection(t_ray *ray, t_cy *c)
{
	t_vec3	top_center;
	double	t_top;
	t_vec3	top_intersection;

	top_center = addition(c->center, multiply(c->normal, c->height / 2));
	t_top = dot_product(substraction(top_center, ray->origin), c->normal)
		/ dot_product(ray->direction, c->normal);
	top_intersection = clash_point(ray, t_top);
	return (dot_product(substraction(top_intersection, top_center),
			substraction(top_intersection, top_center)) <= (c->diameter / 2)
		* (c->diameter / 2));
}

bool	cylinder_shadow(t_ray ray, t_cy *cylinder)
{
	t_quads	solution;
	double	t_hit;

	t_hit = INFINITY;
	quadratic_cylinder(cylinder, ray, &solution);
	if (solution.discriminant < 0)
		return (false);
	if (solution.t1 >= EPSILON)
		check_solution(&ray, cylinder, solution.t1, &t_hit);
	if (solution.t2 >= EPSILON)
		check_solution(&ray, cylinder, solution.t2, &t_hit);
	if (t_hit < INFINITY) 
		return (true);
	return (check_top_intersection(&ray, cylinder));
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

	ray_to_light = substraction(scene->light.lp, rec->clash);
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