/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:05:22 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/24 14:10:09 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec3	get_cylinder_normal(t_vec3 point, t_cy *cylinder)
{
	t_vec3	center_to_point;
	t_vec3	normal;

	center_to_point = substraction(point, cylinder->center);
	normal = substraction(center_to_point, multiply(cylinder->normal,
				dot_product(cylinder->normal, center_to_point)));
	normal = normalize_vector(normal);
	return (normal);
}

void	quadratic_cylinder(t_cy *cylinder,	t_ray ray, t_quads*solution)
{
	t_vec3	a_sqrt;
	t_vec3	right;
	double	abc[3];

	a_sqrt = substraction(ray.direction, multiply(cylinder->normal,
				dot_product(ray.direction, cylinder->normal)));
	abc[0] = dot_product(a_sqrt, a_sqrt);
	right = substraction(substraction(ray.origin, cylinder->center),
			multiply(cylinder->normal, dot_product(substraction(ray.origin,
						cylinder->center), cylinder->normal)));
	abc[1] = 2 * dot_product(a_sqrt, right);
	abc[2] = dot_product(right, right) - ((cylinder->diameter / 2) 
			* (cylinder->diameter / 2));
	solution->discriminant = abc[1] * abc[1] - (4 * abc[0] * abc[2]);
	if (solution->discriminant >= 0)
	{
		solution->t1 = (-abc[1] - sqrt(solution->discriminant)) / (2 * abc[0]);
		solution->t2 = (-abc[1] + sqrt(solution->discriminant)) / (2 * abc[0]);
	}
	else
	{
		solution->t1 = INFINITY;
		solution->t2 = INFINITY;
	}
}