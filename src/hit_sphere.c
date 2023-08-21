/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:52:40 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/19 18:17:00 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// ax^2 + bx + c = 0
// Discriminant (D) = b^2 - 4ac
// x = (-b ± √(D)) / (2a) 
t_quadratic_solution quadratic_sphere(t_vec3 center, double radius, t_ray r)
{
	double	a;
	double	b;
	double	c;
	t_quadratic_solution	solution;
    t_vec3 origin_to_center = substraction(r.origin, center);
    
	a = dot_product(r.direction, r.direction); //skalarni soucin
 	b = 2.0 * dot_product(origin_to_center, r.direction);
	c = dot_product(origin_to_center, origin_to_center) - radius * radius;
	solution.discriminant = b * b - (4 * a * c);
	if (solution.discriminant >= 0)
	{
		solution.t1 = (- b - sqrt(solution.discriminant)) / (2 * a);
        solution.t2 = (- b + sqrt(solution.discriminant)) / (2 * a);
	}
	else
    {
        solution.t1 = INFINITY; // No intersection
        solution.t2 = INFINITY;
    }
	return(solution);
}


/*
calculates normal vector on the surface of the sphere, of the intersection of ray and object
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
	//rec->normal = vect_normalize(vect_sub(rec->p, sp->center));
	//rec->normal = vect_normalize(rec->normal);//myslim ze vypustit
	rec->obj = obj;
	rec->color = sp->color;
	return (true);
}
//nahradit objects za sp