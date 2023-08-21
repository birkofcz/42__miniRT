/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:51:34 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/21 10:48:38 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* To create vector  using t_vec3 struct */
t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3 result;

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

double	vector_len(t_vec3 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y +
													vector.z * vector.z));
}

double length_squared(t_vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
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

bool	is_normal_negative(t_vec3 vec)
{
	if (vec.x < 0 || vec.y < 0 ||vec.z < 0)
		return (true);
	else
		return (false);
}