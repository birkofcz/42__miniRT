/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:25:44 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/23 15:27:13 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec3	direction_vec_creation(t_scene *scene, double u, double v)
{
	t_vec3	horizontal_contribution;
	t_vec3	vertical_contribution;
	t_vec3	horizontal_sum;
	t_vec3	horizontal_and_vertical_sum;

	horizontal_contribution = multiply(scene->cam.horizontal, u);
	vertical_contribution = multiply(scene->cam.vertical, v);
	horizontal_sum = addition(scene->cam.lower_left_corner,
			horizontal_contribution);
	horizontal_and_vertical_sum = addition(horizontal_sum, 
			vertical_contribution);
	return (substraction(horizontal_and_vertical_sum, scene->cam.viewp));
}

t_rgb	ray_color(t_scene *scene)
{
	t_hitrecord	rec;
	t_rgb		result;

	if (hittable_list_hit(scene, &rec))
		return (rec.color);
	result.r = 0;
	result.g = 0;
	result.b = 0;
	return (result);
}
