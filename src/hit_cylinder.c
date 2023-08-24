/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:06 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/24 14:08:27 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
bool	surface_cylinder_hit(t_scene *scene, t_solution)
{
	double projection;

	{
        hit_point = clash_point(&scene->ray, solution.t1);
        projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
        if (projection >= - cylinder->height / 2 && projection <= cylinder->height / 2)
        {
            hit = true;
            t_hit = solution.t1;
			rec->normal = get_cylinder_normal(hit_point, cylinder);
        }
    }

}
*/
/*
bool	hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
    t_cy *cylinder;
    t_quadratic_solution solution;
    t_vec3 hit_point;
	bool hit;
	double t_hit;
	double projection;

	cylinder = obj->object;
	hit = false;
	t_hit = INFINITY;
    quadratic_cylinder(cylinder, scene->ray, &solution);
    // Check intersection with surface
	if (solution.t1 >= scene->ray.t_min && scene->ray.t_max >= solution.t1)
    {
        hit_point = clash_point(&scene->ray, solution.t1);
        projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
        if (projection >= - cylinder->height / 2 && projection <= cylinder->height / 2)
        {
            hit = true;
            t_hit = solution.t1;
			rec->normal = get_cylinder_normal(hit_point, cylinder);
        }
    }
    // Check intersection with bottom cap
	if (is_normal_negative(cylinder->normal))
    {
		double t_bottom = (dot_product(cylinder->normal, substraction(cylinder->center, scene->ray.origin))) / dot_product(scene->ray.direction, cylinder->normal);
		t_vec3 bottom_intersection = clash_point(&scene->ray, t_bottom);
		t_vec3 bottom_center = substraction(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));
		t_bottom = dot_product(substraction(bottom_center, scene->ray.origin), cylinder->normal) / dot_product(scene->ray.direction, cylinder->normal);
		bottom_intersection = clash_point(&scene->ray, t_bottom);

		if (t_bottom >= scene->ray.t_min && t_bottom <= scene->ray.t_max)
		{
			t_vec3 to_intersection = substraction(bottom_intersection, bottom_center);
			double distance_squared = dot_product(to_intersection, to_intersection);

			if (distance_squared <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
			{
				hit = true;
				t_hit = t_bottom;
				hit_point = bottom_intersection;
				t_vec3 normal;
					normal = substraction(hit_point, cylinder->center);
					rec->normal = normalize_vector(normal);
				//rec->normal = cylinder->normal; // Use the cylinder's normal for the cap
			}
		}
	}

    // Check intersection with top cap
    t_vec3 top_center = addition(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));

    double t_top = (dot_product(cylinder->normal, substraction(top_center, scene->ray.origin))) / dot_product(scene->ray.direction, cylinder->normal);
    t_vec3 top_intersection = clash_point(&scene->ray, t_top);
    if (dot_product(substraction(top_intersection, top_center), substraction(top_intersection, top_center)) <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
    {
        if (t_top < t_hit && t_top >= scene->ray.t_min && t_top <= scene->ray.t_max)
        {
            hit = true;
            t_hit = t_top;
            hit_point = top_intersection;
			t_vec3 normal;
			normal = substraction(hit_point, cylinder->center);
    		rec->normal = normalize_vector(normal);
           // rec->normal = cylinder->normal; // same as the cylinder's normal
        }
    }

    if (!hit)
        return (false);
    rec->clash_distance = t_hit;
    rec->type = CYLINDER;
    rec->clash = hit_point;
    rec->obj = obj;
    rec->color = cylinder->color;
    return (true);
}
*/

bool	hit_cylinder_surface(t_object *obj, t_hitrecord *rec, t_cy *cylinder,
		t_ray *ray)
{
	t_quads	solution;
	t_vec3	hit_point;
	double	projec;

	quadratic_cylinder(cylinder, *ray, &solution);
	if (solution.t1 >= ray->t_min && ray->t_max >= solution.t1)
	{
		hit_point = clash_point(ray, solution.t1);
		projec = dot_product(substraction(hit_point, cylinder->center),
				cylinder->normal);
		if (projec >= -cylinder->height / 2 && projec <= cylinder->height / 2)
		{
			rec->normal = get_cylinder_normal(hit_point, cylinder);
			rec->clash_distance = solution.t1;
			rec->clash = hit_point;
			rec->obj = obj;
			rec->color = cylinder->color;
			rec->type = CYLINDER;
			return (true);
		}
	}
	return (false);
}

/* 
double	t_b; - t_bottom
t_vec3	bint - bottom_inter;
t_vec3	bcen - bottom_central
double	dsq; - distance squared
 */

static void	ft_helper_norm(t_hitrecord *rec, double t_b, t_vec3 bint,
		t_object *obj)
{
	rec->clash_distance = t_b;
	rec->clash = bint;
	rec->obj = obj;
}

bool	hit_cylinder_bottom_cap(t_object *obj, t_hitrecord *rec, t_cy *c,
		t_ray *r)
{
	double	t_b;
	t_vec3	bint;
	t_vec3	bcen;
	double	dsq;

	t_b = dot_product(c->normal, substraction(c->center, r->origin)) 
		/ dot_product(r->direction, c->normal);
	bint = clash_point(r, t_b);
	bcen = substraction(c->center, multiply(c->normal, c->height / 2));
	t_b = dot_product(substraction(bcen, r->origin), c->normal) 
		/ dot_product(r->direction, c->normal);
	bint = clash_point(r, t_b);
	if (t_b >= r->t_min && t_b <= r->t_max)
	{
		dsq = dot_product(substraction(bint, bcen), substraction(bint, bcen));
		if (dsq <= (c->diameter / 2) * (c->diameter / 2))
		{
			rec->normal = multiply(c->normal, -1);
			ft_helper_norm(rec, t_b, bint, obj);
			rec->color = c->color;
			rec->type = CYLINDER;
			return (true);
		}
	}
	return (false);
}



bool	hit_cylinder_top_cap(t_object *obj, t_hitrecord *rec, t_cy *c,
	t_ray *ray)
{
	t_vec3	top_center;
	double	t_top;
	t_vec3	top_intersection;

	top_center = addition(c->center, multiply(c->normal, c->height / 2));
	t_top = dot_product(c->normal, substraction(top_center, ray->origin))
		/ dot_product(ray->direction, c->normal);
	top_intersection = clash_point(ray, t_top);
	if (dot_product(substraction(top_intersection, top_center),
			substraction(top_intersection, top_center)) 
		<= (c->diameter / 2) * (c->diameter / 2))
	{
		if (t_top < rec->clash_distance && t_top >= ray->t_min 
			&& t_top <= ray->t_max)
		{
			rec->normal = c->normal;
			rec->clash_distance = t_top;
			rec->clash = top_intersection;
			rec->obj = obj;
			rec->color = c->color;
			rec->type = CYLINDER;
			return (true);
		}
	}
	return (false);
}

bool	hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
	t_cy	*cylinder;
	t_ray	*ray;
	bool	hit;

	cylinder = obj->object;
	ray = &scene->ray;
	hit = false;
	hit = hit_cylinder_surface(obj, rec, cylinder, ray);
	if (!hit && is_normal_negative(cylinder->normal))
		hit = hit_cylinder_bottom_cap(obj, rec, cylinder, ray);
	if (!hit)
		hit = hit_cylinder_top_cap(obj, rec, cylinder, ray);
	return (hit);
}
