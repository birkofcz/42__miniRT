/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:05:27 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/25 15:36:08 by sbenes           ###   ########.fr       */
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

t_rgb	calculate_cylinder_diffuse(t_hitrecord *rec, t_scene *scene, 
	t_vec3 light_normalized)
{
	t_rgb	diff;
	double	pd;
	double	curved_diffuse;

	pd = dot_product(rec->normal, light_normalized);
	curved_diffuse = pd * scene->light.bright_ratio;
	if (pd > 0)
	{
		diff = color_scalar(rec->color, curved_diffuse);
		diff = apply_ambient(diff, scene->amb);
	}
	else
	{
		diff = color_scalar(rec->color, curved_diffuse * scene->amb.ratio);
		diff = apply_ambient(diff, scene->amb);
	}
	diff = color_clamp(diff);
	return (diff);
}

t_rgb	calculate_sphere_diffuse(t_hitrecord *rec, t_scene *scene, double dot)
{
	t_rgb	diff;

	diff = color_scalar(rec->color, (dot * scene->light.bright_ratio));
	diff = color_clamp(diff);
	diff = apply_ambient(diff, scene->amb);
	return (diff);
}
