/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:51:34 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/23 15:48:56 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* To create vector  using t_vec3 struct */
t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec3	normalize_vector(t_vec3 vector)
{
	t_vec3	normal;
	double	len;

	len = sqrt(vector.x * vector.x + vector.y
			* vector.y + vector.z * vector.z);
	normal.x = vector.x / len;
	normal.y = vector.y / len;
	normal.z = vector.z / len;
	return (normal);
}

t_vec3	substraction(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_vec3	addition(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec3	multiply(t_vec3 vec1, double x)
{
	t_vec3	result;

	result.x = vec1.x * x;
	result.y = vec1.y * x;
	result.z = vec1.z * x;
	return (result);
}
