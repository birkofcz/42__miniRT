/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:24:42 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/21 12:54:31 by tkajanek         ###   ########.fr       */
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
/*
bool cylinder_shadow(t_ray ray, t_cy *cylinder)
{
	t_quadratic_solution solution;
	t_vec3 hit_point;
	double projection;
	double t_hit;

	quadratic_cylinder(cylinder, ray, &solution);
	if (solution.discriminant < 0)
		return false;
	t_hit = solution.t1;
	if (t_hit < EPSILON)
		return false;
	hit_point = clash_point(&ray, t_hit);
	t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
	projection = dot_product(hit_to_center, cylinder->normal);
	if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
		return true;
	t_vec3 top_center = addition(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));
	double t_top = dot_product(substraction(top_center, ray.origin), cylinder->normal) / dot_product(ray.direction, cylinder->normal);
	t_vec3 top_intersection = clash_point(&ray, t_top);
	if (dot_product(substraction(top_intersection, top_center), substraction(top_intersection, top_center)) <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
		return true;

	return false;
}*/

bool cylinder_shadow(t_ray ray, t_cy *cylinder)
{
	t_quadratic_solution solution;
	t_vec3 hit_point;
	double projection;
	double t_hit;

	quadratic_cylinder(cylinder, ray, &solution);
	if (solution.discriminant < 0)
		return false;

	t_hit = INFINITY; // Initialize t_hit to a large value

	if (solution.t1 >= EPSILON) // Check if t1 is a valid hit
	{
		hit_point = clash_point(&ray, solution.t1);
		t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
		projection = dot_product(hit_to_center, cylinder->normal);

		if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
		{
			t_hit = solution.t1; // Update t_hit with t1 if it's a valid hit
		}
	}

	if (solution.t2 >= EPSILON) // Check if t2 is a valid hit
	{
		hit_point = clash_point(&ray, solution.t2);
		t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
		projection = dot_product(hit_to_center, cylinder->normal);

		if (projection >= -cylinder->height / 2 && projection <= cylinder->height / 2)
		{
			t_hit = fmin(t_hit, solution.t2); // Update t_hit with min of t_hit and t2 if it's a valid hit
		}
	}

	if (t_hit < INFINITY)
		return true;

	t_vec3 top_center = addition(cylinder->center, multiply(cylinder->normal, cylinder->height / 2));
	double t_top = dot_product(substraction(top_center, ray.origin), cylinder->normal) / dot_product(ray.direction, cylinder->normal);
	t_vec3 top_intersection = clash_point(&ray, t_top);
	if (dot_product(substraction(top_intersection, top_center), substraction(top_intersection, top_center)) <= (cylinder->diameter / 2) * (cylinder->diameter / 2))
		return true;

	return false;
}


/*bool cylinder_shadow(t_ray ray, t_cy *cylinder)
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
	hit_point = clash_point(&ray, t_hit);
   	t_vec3 hit_to_center = substraction(hit_point, cylinder->center);
    projection = dot_product(hit_to_center, cylinder->normal);
	if (projection < -cylinder->height / 2 || projection > cylinder->height / 2)
		return (false);
	return (true);
}*/

bool	intersect_shadow(t_ray ray, t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(ray, obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_shadow(ray, obj->object));
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