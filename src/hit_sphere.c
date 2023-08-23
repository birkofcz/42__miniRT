/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:52:40 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/22 17:36:23 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
ax^2 + bx + c = 0
Discriminant (D) = b^2 - 4ac
x = (-b ± √(D)) / (2a)
t is set to infinity when there is no interestion
*/
t_quadratic_solution quadratic_sphere(t_vec3 center, double radius, t_ray r)
{
	double	a;
	double	b;
	double	c;
	t_quadratic_solution	solution;

	a = dot_product(r.direction, r.direction);
	b = 2.0 * dot_product(substraction(r.origin, center), r.direction);
	c = dot_product(substraction(r.origin, center), substraction(r.origin, center))
		- radius * radius;
	solution.discriminant = b * b - (4 * a * c);
	if (solution.discriminant >= 0)
	{
		solution.t1 = (- b - sqrt(solution.discriminant)) / (2 * a);
		solution.t2 = (- b + sqrt(solution.discriminant)) / (2 * a);
	}
	else
	{
		solution.t1 = INFINITY;
		solution.t2 = INFINITY;
	}
	return(solution);
}

/*
calculates normal vector on the surface of the sphere,
of the intersection of ray and object.
*/
t_vec3	get_sphere_normal(t_vec3 clash, t_sp *sphere)
{
	t_vec3 normal;

	normal = substraction(clash, sphere->center);
	normal = normalize_vector(normal);
	return (normal);
}

bool	hit_sphere(t_scene *scene, t_hitrecord *rec, t_object *obj)
{
	t_sp	*sp;
	t_quadratic_solution	solution;

	sp = (t_sp *) obj->object;
	solution = quadratic_sphere(sp->center, sp->diameter / 2, scene->ray);
	if (solution.discriminant < 0)
		return (false);
	if (solution.t1 < scene->ray.t_min || scene->ray.t_max < solution.t1)
		return (false);
	rec->clash_distance = solution.t1;
	rec->type = SPHERE;
	rec->clash = clash_point(&scene->ray, rec->clash_distance);
	rec->normal = get_sphere_normal(rec->clash, sp);
	rec->obj = obj;
	rec->color = sp->color;
	return (true);
}
