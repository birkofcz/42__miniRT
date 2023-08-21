/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:06 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/19 11:14:49 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
/*
bool hit_cylinder(t_data *data, t_hitrecord *rec, t_object *obj)
{
    t_cy	*cylinder;
    t_quadratic_solution solution;
    t_ray rotated_ray;
    t_mat4 matrix;
    double y;

    cylinder = obj->object;

    // Rotate the ray by the cylinder's normal using a rotation matrix
 	matrix = mat4_rotate(cylinder->normal);
    initialize_rotated_ray(&rotated_ray, data->r, matrix);

    // Calculate quadratic solution for the rotated ray and the cylinder
    solution = calculate_quadratic_cylinder(rotated_ray, cylinder);

    // Check if no real solutions for the quadratic equation (no intersection)
    if (solution.delta <= 0)
    {
        return false; // No intersection
    }

    // Find the closest hit point using the quadratic solutions
    if (!get_closet_hit(rotated_ray, rec, cy, solution))
    {
        return false; // No valid hit within the solution range
    }

    // Calculate hit point in world space
    rec->p = ray_hit_point(&rotated_ray, rec->hit_point_distance);

    // Calculate 'y' coordinate relative to the cylinder's center
    y = rec->p.y - cy->center.y;

    // Rotate the normal vector back to world space
    matrix= mat4_rotate(vect_scale(cy->normal, -1));
    rec->normal = calculate_normal(rec, cy, matrix, y);

    // Set hit record properties
    rec->type = CYLINDER;
    rec->color = cy->color;
    rec->obj = obj;

    return true; // Ray intersects with the cylinder
}
*/


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



void		quadratic_cylinder(t_cy *cylinder,	t_ray ray, t_quadratic_solution *solution)
{
	t_vec3	a_sqrt;
	t_vec3	right;
	double	a;
	double	b;
	double	c;

	a_sqrt = substraction(ray.direction,
				multiply(cylinder->normal, dot_product(ray.direction, cylinder->normal)));
	a = dot_product(a_sqrt, a_sqrt);
	right = substraction(substraction(ray.origin, cylinder->center),
						multiply(cylinder->normal,
							dot_product(substraction(ray.origin, cylinder->center),
							cylinder->normal)));
	b = 2 * dot_product(a_sqrt, right);
	c = dot_product(right, right) - ((cylinder->diameter / 2) * (cylinder->diameter / 2));
	solution->discriminant = b * b - (4 * a * c);
	if (solution->discriminant >= 0)
	{
		solution->t1 = ( - b - sqrt(solution->discriminant)) / (2 * a);
        solution->t2 = ( - b + sqrt(solution->discriminant)) / (2 * a);
	}
	else
    {
        solution->t1 = INFINITY; // No intersection
        solution->t2 = INFINITY;
    }
	return;
}

/* Original code */
/* bool hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
    t_cy *cylinder = obj->object;
    t_quadratic_solution solution;
    t_vec3 hit_point;
    double projection;

    quadratic_cylinder(cylinder, scene->ray, &solution);
    if (solution.discriminant < 0)
        return false;

    bool hit = false;
    double t_hit = INFINITY;

    // Check intersection with surface
    if (solution.t1 >= scene->ray.t_min && scene->ray.t_max >= solution.t1)
    {
        hit_point = clash_point(&scene->ray, solution.t1);
        projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
        if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
        {
            hit = true;
            t_hit = solution.t1;
        }
    }

    if (!hit && solution.t2 >= scene->ray.t_min && scene->ray.t_max >= solution.t2)
    {
        hit_point = clash_point(&scene->ray, solution.t2);
        projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
        if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
        {
            hit = true;
            t_hit = solution.t2;
        }
    }

    if (!hit)
        return false;
    // Set other hit record properties
    rec->clash_distance = t_hit;
    rec->type = CYLINDER;
    rec->clash = hit_point;
    rec->obj = obj;
    rec->color = cylinder->color;
	rec->normal = get_cylinder_normal(hit_point, cylinder);
    return true;
} */

/* TOP AND BOTTOM CAPS */
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
	 if (solution.t1 >= scene->ray.t_min && scene->ray.t_max >= solution.t1)
    {
        hit_point = clash_point(&scene->ray, solution.t1);
        projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
        if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
        {
            hit = true;
            t_hit = solution.t1;
        }
    }

    if (!hit && solution.t2 >= scene->ray.t_min && scene->ray.t_max >= solution.t2)
    {
        hit_point = clash_point(&scene->ray, solution.t2);
        projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
        if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
        {
            hit = true;
            t_hit = solution.t2;
        }
    }
	
    // Check intersection with bottom cap
    double t_bottom = (dot_product(cylinder->normal, substraction(cylinder->center, scene->ray.origin))) / dot_product(scene->ray.direction, cylinder->normal);
    t_vec3 bottom_intersection = clash_point(&scene->ray, t_bottom);
   	if (dot_product(substraction(bottom_intersection, cylinder->center), substraction(bottom_intersection, cylinder->center)) <= (cylinder->diameter / 4) * (cylinder->diameter / 4))
    {
        if (t_bottom < t_hit && t_bottom >= scene->ray.t_min && t_bottom <= scene->ray.t_max)
		
        {
            hit = true;
            t_hit = t_bottom;
            hit_point = bottom_intersection;
            rec->normal = multiply(cylinder->normal, -1); // inverse of the cylinder's normal
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
            rec->normal = cylinder->normal; // same as the cylinder's normal
        }
    }

    if (!hit)
        return false;

    // Set other hit record properties
    rec->clash_distance = t_hit;
    rec->type = CYLINDER;
    rec->clash = hit_point;
    rec->obj = obj;
    rec->color = cylinder->color;
	rec->normal = get_cylinder_normal(hit_point, cylinder);
    return true;
}





/*
bool hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
	t_cy	*cylinder;
    t_quadratic_solution solution;
	t_vec3 hit_point;
	double projection;

	cylinder = obj->object;
	quadratic_cylinder(cylinder, scene->ray, &solution);

	if (solution.discriminant < 0)
        return false;
	if (solution.t1 < scene->ray.t_min || scene->ray.t_max < solution.t1)
		return (false);

	hit_point = clash_point(&scene->ray, solution.t1);
	projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
	// Check if the hit point is within the capped regions	

 if (projection <= -cylinder->height / 2)
    {
        hit_point = clash_point(&scene->ray, solution.t1);
        rec->normal = create_vec3(0, -1, 0); // Bottom cap normal
    }
    else if (projection >= cylinder->height / 2)
    {
        hit_point = clash_point(&scene->ray, solution.t1);
        rec->normal = create_vec3(0, 1, 0); // Top cap normal
    }

	if (projection < (-cylinder->height / 2) || projection > (cylinder->height / 2))
		return (false);
	rec->clash_distance = solution.t1;
    rec->type = CYLINDER;
    rec->clash = hit_point;
    rec->normal = get_cylinder_normal(hit_point, cylinder);
    rec->obj = obj;
    rec->color = cylinder->color;
	return (true);
}
*/