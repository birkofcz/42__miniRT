/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:24:42 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/25 15:33:54 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	apply_ambient(t_rgb object_color, t_amb amb)
{
	t_rgb	ambient_contribution;

	ambient_contribution.r = ((object_color.r + amb.color.r * amb.ratio));
	ambient_contribution.g = ((object_color.g + amb.color.g * amb.ratio));
	ambient_contribution.b = ((object_color.b + amb.color.b * amb.ratio));
	ambient_contribution = color_clamp(ambient_contribution);
	return (ambient_contribution);
}

t_rgb	apply_ambient_shadow(t_rgb object_color, t_amb amb)
{
	t_rgb	ambient_contribution;

	ambient_contribution.r = ((object_color.r + amb.color.r) / 2) * amb.ratio;
	ambient_contribution.g = ((object_color.g + amb.color.g) / 2) * amb.ratio;
	ambient_contribution.b = ((object_color.b + amb.color.b) / 2) * amb.ratio;
	ambient_contribution = color_clamp(ambient_contribution);
	return (ambient_contribution);
}

/* void	calculate_diffuse(t_scene *scene, t_hitrecord *rec, double dot)
{
	t_rgb		diff;
	t_vec3		light_normalized;
	double		pd;

	light_normalized = normalize_vector(scene->light.lp);
	if (rec->type == SPHERE)
	{
		diff = color_scalar(rec->color, (dot * scene->light.bright_ratio));
		diff = color_clamp(diff);
		rec->color = diff;
		rec->color = apply_ambient(rec->color, scene->amb);
	}
	else if (rec->type == CYLINDER)
	{
		pd = dot_product(rec->normal, light_normalized);
		double curved_diffuse = pd * scene->light.bright_ratio;
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
			rec->color = diff;
		}
	else if (rec->type == PLANE)
	{
		pd = dot_product(rec->normal, light_normalized);
		if (pd > 0 && ((pd * scene->light.bright_ratio) > scene->amb.ratio))
		{
			diff = color_scalar(rec->color, (pd * scene->light.bright_ratio));
			rec->color = diff;
			rec->color = apply_ambient(rec->color, scene->amb);
			rec->color = color_clamp(rec->color);
		}
		else
			rec->color = apply_ambient(rec->color, scene->amb);
	}
} */

void	calculate_diffuse(t_scene *scene, t_hitrecord *rec, double dot)
{
	t_rgb	diff;
	t_vec3	light_normalized;
	double	pd;

	light_normalized = normalize_vector(scene->light.lp);
	if (rec->type == SPHERE)
		rec->color = calculate_sphere_diffuse(rec, scene, dot);
	else if (rec->type == CYLINDER)
		rec->color = calculate_cylinder_diffuse(rec, scene, light_normalized);
	else if (rec->type == PLANE)
	{
		pd = dot_product(rec->normal, light_normalized);
		if (pd > 0 && ((pd * scene->light.bright_ratio) > scene->amb.ratio))
		{
			diff = color_scalar(rec->color, (pd * scene->light.bright_ratio));
			rec->color = diff;
			rec->color = apply_ambient(rec->color, scene->amb);
			rec->color = color_clamp(rec->color);
		}
		else
			rec->color = apply_ambient(rec->color, scene->amb);
	}
}

/*
if hit_point is in shadow, the shadow is calculated.

normalized vector is the direction from the hit point to the light source,
and rec->normal is the normalized surface normal vector at the hit point.

Dot product between the two vectors gives the cosine of the angle θ between them:
dot = cos(θ)

In lighting calculations,the cosine of the angle
between the light direction and the surface normal 
determines how much the light is directly illuminating
the surface at that point. A higher cosine value means
the light is more directly facing the surface.

fmax ensures the dot product is not negative.
*/
void	calculate_and_apply_light(t_scene *scene, t_hitrecord *rec, bool shadow)
{
	double		dot;
	t_vec3		light_normalized;

	if (shadow)
	{
		rec->color = apply_ambient_shadow(rec->color, scene->amb);
		return ;
	}
	light_normalized = normalize_vector(scene->light.lp);
	dot = fmax(dot_product(light_normalized, rec->normal), 0.0);
	if (dot < scene->amb.ratio)
		dot = scene->amb.ratio;
	calculate_diffuse(scene, rec, dot);
}

void	apply_light(t_scene *scene, t_hitrecord *rec)
{
	bool	shadow;

	shadow = is_in_shadow(scene, rec);
	calculate_and_apply_light(scene, rec, shadow);
}
