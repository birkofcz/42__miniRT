/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:44:54 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/24 16:24:52 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	is_normal_negative(t_vec3 vec)
{
	if (vec.x < 0 || vec.y < 0 || vec.z < 0)
		return (true);
	else
		return (false);
}

double	vector_len(t_vec3 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y 
			+ vector.z * vector.z));
}

double	length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

double	dot_product(t_vec3 a, t_vec3 b)
{
	double	sum;

	sum = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (sum);
}
