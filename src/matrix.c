/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:10:30 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/16 15:28:14 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
/*
An identity matrix is a square matrix in which all the diagonal elements are 1,
and all the non-diagonal elements are 0. When you multiply any matrix by it,
the result is the same matrix. It acts like the "multiplicative identity" for matrices.
Identity matrices are used as a starting point for transformations, projections,
and view matrices.

| 1 0 0 0 |
| 0 1 0 0 |
| 0 0 1 0 |
| 0 0 0 1 |

*/
t_mat4	mat4_identity(void)
{
	t_mat4	mat;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat.m[i][j] = 0;
			if (i == j)
				mat.m[i][j] = 1;
			j++;
		}
		i++;
	}
	return (mat);
}

t_mat4	mat4_mult(t_mat4 a, t_mat4 b)
{
	t_mat4	mat;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			mat.m[i][j] = 0;
			k = -1;
			while (++k < 4)
				mat.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (mat);
}

t_mat4	mat4_scale(t_vec3 v)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = v.x;
	mat.m[1][1] = v.y;
	mat.m[2][2] = v.z;
	return (mat);
}

t_mat4	mat4_translate(t_vec3 v)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][3] = v.x;
	mat.m[1][3] = v.y;
	mat.m[2][3] = v.z;
	return (mat);
}

t_mat4	mat4_rotate_x(double angle)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[1][1] = cos(angle);
	mat.m[1][2] = -sin(angle);
	mat.m[2][1] = sin(angle);
	mat.m[2][2] = cos(angle);
	return (mat);
}

t_mat4	mat4_rotate_y(double angle)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = cos(angle);
	mat.m[0][2] = sin(angle);
	mat.m[2][0] = -sin(angle);
	mat.m[2][2] = cos(angle);
	return (mat);
}

t_mat4	mat4_rotate_z(double angle)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.m[0][0] = cos(angle);
	mat.m[0][1] = -sin(angle);
	mat.m[1][0] = sin(angle);
	mat.m[1][1] = cos(angle);
	return (mat);
}

t_mat4	mat4_rotate(t_vec3 v)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat = mat4_mult(mat4_rotate_x(v.x), mat);
	mat = mat4_mult(mat4_rotate_y(v.y), mat);
	mat = mat4_mult(mat4_rotate_z(v.z), mat);
	return (mat);
}

t_vec3	mat4_mult_vec3(t_mat4 m, t_vec3 v)
{
	t_vec3	res;

	res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	res.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
	return (res);
}