/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:24:42 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/22 17:54:09 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double ft_clamp(double value, double min, double max)
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

t_rgb	apply_ambient(t_rgb object_color, t_amb amb)
{
	t_rgb ambient_contribution;

	ambient_contribution.r = ((object_color.r + amb.color.r * amb.ratio));
	ambient_contribution.g = ((object_color.g + amb.color.g * amb.ratio));
	ambient_contribution.b = ((object_color.b + amb.color.b * amb.ratio));
	ambient_contribution = color_clamp(ambient_contribution);
	return (ambient_contribution);
}

t_rgb	apply_ambient_shadow(t_rgb object_color, t_amb amb)
{
	t_rgb ambient_contribution;

	ambient_contribution.r = ((object_color.r + amb.color.r) / 2 )* amb.ratio;
	ambient_contribution.g = ((object_color.g + amb.color.g) / 2 ) * amb.ratio;
	ambient_contribution.b = ((object_color.b + amb.color.b) / 2 ) * amb.ratio;
	ambient_contribution = color_clamp(ambient_contribution);
	return (ambient_contribution);
}
void	calculate_diffuse(t_scene *scene, t_hitrecord *rec, double dot)
{
	t_rgb		diffuse;
	t_vec3		light_normalized;

	light_normalized = normalize_vector(scene->light.lightpoint);
	if (rec->type == SPHERE || rec->type == CYLINDER)
	{
		diffuse = color_scalar(rec->color,
				(dot * scene->light.bright_ratio));
		diffuse = color_clamp(diffuse);
		
		rec->color = diffuse;
		rec->color = apply_ambient(rec->color, scene->amb);
	}
	else if (rec->type == PLANE)
    {
        double plane_dot = dot_product(rec->normal, light_normalized);
        if (plane_dot > 0 && ((plane_dot * scene->light.bright_ratio) > scene->amb.ratio))
        {
				diffuse = color_scalar(rec->color,
                	(plane_dot * scene->light.bright_ratio));
           		 rec->color = diffuse;
				 rec->color = apply_ambient(rec->color, scene->amb);
           		 rec->color = color_clamp(rec->color);
        }
		else
        {
            rec->color = apply_ambient(rec->color, scene->amb);
        }
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
		//rec->color = color_scalar(rec->color, scene->amb.ratio);
		return ;
	}
	light_normalized = normalize_vector(scene->light.lightpoint);
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