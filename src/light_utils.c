/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:05:27 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/23 15:05:55 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	ft_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

t_rgb	color_clamp(t_rgb color)
{
	t_rgb	tmp;

	tmp.r = ft_clamp(color.r, 0.0, 255.0);
	tmp.g = ft_clamp(color.g, 0.0, 255.0);
	tmp.b = ft_clamp(color.b, 0.0, 255.0);
	return (tmp);
}

t_rgb	color_scalar(t_rgb color, double scalar)
{
	color.r *= scalar;
	color.g *= scalar;
	color.b *= scalar;
	return (color);
}
