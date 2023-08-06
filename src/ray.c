/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:17:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/06 16:22:19 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}
