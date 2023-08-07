/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:52:40 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/07 18:11:37 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/*
point: This is the three-dimensional vector representing a point in space.
It is the point for which you want to calculate the normal vector on the surface of the sphere.
*/
t_vec3	get_sphere_normal(t_vec3 point, t_sp sphere)
{
	t_vec3 normal;

	normal = substraction(point, sphere.center);
	normal = normalize_vector(normal);
	return (normal);
}

/*
int	get_roots(double *t0, double *t1, t_ray ray, t_sphere sphere)
{
	t_v3	l;
	double	a;
	double	b;
	double	c;

	l = substract(ray.origin, sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(ray.direction, l);
	c = dot_product(l, l) - (sphere.radius * sphere.radius);
	if (solve_quadratic(new_qparams(a, b, c), t0, t1) == 0)
		return (0);
	return (1);
}*/

bool hit_sphere(t_vec3 center, double radius, t_ray r)
 {
	double	a;
	double	b;
	double	c;
	double discriminant;

    t_vec3 origin_to_center = substraction(r.origin, center);
    
	a = dot_product(r.direction, r.direction); //skalarni soucin
 	b = 2.0 * dot_product(origin_to_center, r.direction);
	c = dot_product(origin_to_center, origin_to_center) - radius * radius;
	discriminant = b * b - (4 * a * c);
	if (discriminant > 0)
		return (true);
	else
		return (false);
}

t_rgb ray_color(t_ray ray, t_scene *scene)
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
}
