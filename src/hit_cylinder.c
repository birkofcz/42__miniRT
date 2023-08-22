/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:06 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/22 18:38:03 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec3		get_cylinder_normal(t_vec3 point, t_cy *cylinder)
{
	t_vec3 center_to_point;
	t_vec3 normal;

	center_to_point = substraction(point, cylinder->center);
	normal = substraction(center_to_point, multiply(cylinder->normal,
		dot_product(cylinder->normal, center_to_point)));
	normal = normalize_vector(normal);
	return (normal);
}

void	quadratic_cylinder(t_cy *cylinder,	t_ray ray, t_quadratic_solution *solution)
{
	t_vec3	a_sqrt;
	t_vec3	right;
	double	abc[3];

	a_sqrt = substraction(ray.direction,
				multiply(cylinder->normal, dot_product(ray.direction, cylinder->normal)));
	abc[0] = dot_product(a_sqrt, a_sqrt);
	right = substraction(substraction(ray.origin, cylinder->center),
				multiply(cylinder->normal,
					dot_product(substraction(ray.origin, cylinder->center),
					cylinder->normal)));
	abc[1] = 2 * dot_product(a_sqrt, right);
	abc[2] = dot_product(right, right) - ((cylinder->diameter / 2) * (cylinder->diameter / 2));
	solution->discriminant = abc[1] * abc[1] - (4 * abc[0] * abc[2]);
	if (solution->discriminant >= 0)
	{
		solution->t1 = ( - abc[1] - sqrt(solution->discriminant)) / (2 * abc[0]);
        solution->t2 = ( - abc[1] + sqrt(solution->discriminant)) / (2 * abc[0]);
	}
	else
    {
        solution->t1 = INFINITY;
        solution->t2 = INFINITY;
    }
}

bool hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
    t_cy *cylinder = obj->object;
    t_quadratic_solution solution;
    t_vec3 hit_point;
    double projection;

	

	//cylinder->normal = normalize(cylinder->normal);


    quadratic_cylinder(cylinder, scene->ray, &solution);

    bool hit = false;
    double t_hit = INFINITY;

    // Check intersection with surface
    // ... (existing code to check intersection with cylinder's surface) ...
	hit = false;
	t_hit = INFINITY;
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
