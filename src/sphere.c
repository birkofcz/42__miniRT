/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:52:40 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/06 16:35:41 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
point: This is the three-dimensional vector representing a point in space.
It is the point for which you want to calculate the normal vector on the surface of the sphere.
*/
t_vec3	get_sphere_normal(t_vec3 point, t_sp sphere)
{
	t_vec3 normal;

	normal = substract(point, sphere.center);
	normalize_vector(&normal);
	return (n);
}

/*
int	get_roots(double *t0, double *t1, t_ray ray, t_sphere sphere)
{
	t_v3	l;
	double	a;
	double	b;
	double	c;

	l = substract(ray.origin, sphere.center);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(ray.direction, l);
	c = dot_product(l, l) - (sphere.radius * sphere.radius);
	if (solve_quadratic(new_qparams(a, b, c), t0, t1) == 0)
		return (0);
	return (1);
}*/

bool hit_sphere(t_vec3 point, double radius, t_ray r)
 {
	double	a;
	double	b;
	double	c;
	double discriminant;

    t_vec3 origin_to_center = subtract(r.origin, center);
    
	a = dot_product(r.direction, r.direction); //skalarni soucin
 	b = 2.0 * dot_product(origin_to_center, r.direction);
	c = dot_product(origin_to_center, origin_to_center) - radius * radius;
	discriminant = b * b - (4 * a * c);
	if (discriminant > 0)
		return (true);
	else
		return (false);
}

t_color ray_color(ray ray)
{

    if (hit_sphere(scene->center, scene->diameter / 2, ray))
        return (t_color) {1, 0, 0};

    vec3 unit_direction = normalize_vector(r.direction);
    double t = 0.5 * (unit_direction.y + 1.0);

    color white = {1.0, 1.0, 1.0};
    color blue = {0.5, 0.7, 1.0};

    color c1, c2, result;
    c1.x = (1.0 - t) * white.x;
    c1.y = (1.0 - t) * white.y;
    c1.z = (1.0 - t) * white.z;

    c2.x = t * blue.x;
    c2.y = t * blue.y;
    c2.z = t * blue.z;

    result.x = c1.x + c2.x;
    result.y = c1.y + c2.y;
    result.z = c1.z + c2.z;

    return result;
}
