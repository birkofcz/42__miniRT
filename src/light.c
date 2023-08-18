/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:24:42 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/18 16:28:41 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	sphere_shadow(t_ray ray, t_sp *sphere)
{
	t_quadratic_solution	solution;

	solution = quadratic_sphere(sphere->center, sphere->diameter / 2, ray);
	if (solution.discriminant < 0)
		return (false);
	if (solution.t1 > EPSILON || solution.t2 > EPSILON)
		return (true);
	return (false);
}

/*
mozna vyradit t_hit, pokud nemusime urcovat ktery stycny bod je driv
*/
bool cylinder_shadow(t_ray ray, t_cy *cylinder)
{
	t_quadratic_solution solution;
	t_vec3 hit_point;
	double projection;
	double t_hit;
    
    quadratic_cylinder(cylinder, ray, &solution);
	if (solution.discriminant < 0)
		return (false);
	t_hit = solution.t1;
	if (t_hit < EPSILON)
		return (false);
	//rekl bych ze zde je problem. vyhodnoti to jako styk co je bliz
	hit_point = clash_point(&ray, t_hit);/*
	projection = dot_product(substraction(hit_point, cylinder->center), cylinder->normal);
    */
   	t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
    projection = dot_product(hit_to_center, cylinder->normal);
   // double distance_to_center = vector_len(hit_to_center);
	// Check if the hit point is within the lateral surface of the cylinder
	if (projection < -cylinder->height / 2 || projection > cylinder->height / 2)
		return (false);
    // Check if the hit point is within the top cap
	//if (dot_product(hit_to_center, cylinder->normal) < 0)
	//{
	//	if (distance_to_center > cylinder->diameter / 2)
	//		return (false);
	//}
	return (true);
}

bool	intersect_shadow(t_ray ray, t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(ray, obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_shadow(ray, obj->object));
//	else if (obj->type == PLANE)
//		return plane_shadow(ray, obj->object);
	return (false);
}

/*
Casting a shadow ray from the point of intersection
toward the light source and checking
if the ray intersects with any objects in the scene
before it reaches the light. If an intersection is found,
it means the point is in shadow; otherwise, it's illuminated.
*/


bool	is_in_shadow(t_scene *scene, t_hitrecord *rec)
{
	t_vec3		ray_to_light;
	t_ray		shadow_ray;
	t_object	*tmp;

	ray_to_light = substraction(scene->light.lightpoint, rec->clash);
	shadow_ray.origin = rec->clash;
	shadow_ray.direction = normalize_vector(ray_to_light);
	tmp = scene->head_object;
	while (tmp)
	{
		if (tmp == rec->obj)
		{
			tmp = tmp->next;
			continue ;
		}
		if (intersect_shadow(shadow_ray, tmp))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_rgb	color_clap(t_rgb color)
{
	t_rgb	tmp;

	tmp = color;
	if (tmp.r > 255)
		tmp.r = 255;
	if (tmp.g > 255)
		tmp.g = 255;
	if (tmp.b > 255)
		tmp.b = 255;
	return (tmp);
}

t_rgb	color_scalar(t_rgb color, double scalar)
{
	color.r *= scalar;
	color.g *= scalar;
	color.b *= scalar;
	return (color);
}

void	calculate_diffuse(t_scene *scene, t_hitrecord *rec, double dot)
{
	t_rgb		diffuse;
	t_vec3		light_normalized;

	light_normalized = normalize_vector(scene->light.lightpoint);
	if (rec->type == SPHERE)
	{
		diffuse = color_scalar(rec->color,
				(dot * scene->light.bright_ratio));
		rec->color = diffuse;
		rec->color = color_clap(rec->color);
	}
	else if (rec->type == CYLINDER)
	{
		rec->color = color_scalar(rec->color,
				(dot * scene->light.bright_ratio));
		rec->color = color_clap(rec->color);
	}
}



/*
if shadow calculates the shadow part.
dot = fmax(vect_dot(light_normalized, rec->normal), 0.0);
normalized vector is the direction from the hit point to the light source,
and rec->normal is the normalized surface normal vector at the hit point.

Dot product between the two vectors gives the cosine of the angle θ between them:
dot = cos(θ)

In lighting calculations,
the cosine of the angle between the light direction and the surface normal 
determines how much the light is directly illuminating the surface at that point.
A higher cosine value means the light is more directly facing the surface.

fmax ensures the dot product is not negative.
*/
void	calculate_and_apply_light(t_scene *scene, t_hitrecord *rec, bool shadow)
{
	double		dot;
	t_vec3		light_normalized;

	if (shadow)
	{
		rec->color = color_scalar(rec->color, scene->amb.ratio);
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