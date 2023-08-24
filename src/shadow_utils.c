/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:36:46 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/24 14:40:34 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	sphere_shadow(t_ray ray, t_sp *sphere)
{
	t_quads	solution;

	solution = quadratic_sphere(sphere->center, sphere->diameter / 2, ray);
	if (solution.discriminant < 0)
		return (false);
	if (solution.t1 > EPSILON || solution.t2 > EPSILON)
		return (true);
	return (false);
}
