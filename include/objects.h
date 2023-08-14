/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:56 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/12 19:18:48 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"
# include "vec3.h"
# include "color.h"

/* Ambient lightning
identifier: A
ratio - ambient lightning ratio in range [0.0,1.0]
color - colors in range [0-255] 
*/
typedef struct s_ambientlight
{
	double	ratio;
	t_rgb	color;
}	t_amb;

/* Camera 
identifier: C
xyz coordinates of the viewpoint
vec3 - 3d normalized orientation vector for each axis
fov - horizontal field of view in degrees in range [0,180]
 */
typedef struct s_camera
{
	t_vec3	viewpoint;
	t_vec3	normal;
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	lower_left_corner;
	double	fov;
	double	fov_rad;
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	double	aspect_ratio;
}	t_cam;

/* Light
identifier: L
xyz - coordinates of the lightpoint
bright_ratio - light brightness ratio in range [0.0,1.0]
 */
typedef struct s_light
{
	t_vec3	lightpoint;
	double	bright_ratio;
}	t_light;

/* Sphere - object
identifier: sp
xyz - coordinates of the sphere center
diameter - the sphere diameter
rgb - rgb colors in range [0-255]
 */
typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	t_rgb	color;
}	t_sp;

/* Plane - object
identifier: pl
xyz - coordinates of the point in the plane
vx,vy,vz - 3d normalized normal vector. In range [-1,1] for each axis
rgb - colors in range [0-255]
 */
typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_rgb	color;
}	t_pl;

/* Cylinder - object
identifier: cy
xyz - coordinates of the center of the cylinder
vx,vy,vz - 3d normalized vector of axis of the cylinder. In range [-1,1] 
for each axis
diameter - the cylinder diameter
height - the cylinder height
rgb - rgb colors in range [0-255]
 */
typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	normal;
	double	diameter;
	double	height;
	t_rgb	color;
}	t_cy;

typedef struct s_mlxdata
{
	void	*mlx_p;
	void	*win_p;
	void	*img_p;
	char	*img_data;
	int		bpp;
	int		line_size;
	int	img_height;
	int img_width;
}	t_mlxdata;

typedef enum e_type
{
	NONE,
	SPHERE,
	PLANE,
	CYLINDER
}				t_type;

typedef struct s_object
{
	t_type			type;
	void			*object;
	struct s_object	*next;
}				t_object;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	double	t_min;
	double	t_max;
}	t_ray;

typedef struct s_scene
{
	t_amb	amb;
	t_cam	cam;
	t_light	light;
	//t_sp	*sp;
	//t_pl	*pl;
	//t_cy	*cy;
	t_object *head_object;
	t_object *object;
	int		sphere_count;
	int		plane_count;
	int		cylinder_count;
	t_rgb **pixel_map;
	t_ray	ray;//aktualni paprsek v reseni.

}	t_scene;

typedef struct	s_pixel{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}				t_pixel;


/*
t_min = lower bound for valid intersection distances along the ray.
t_max = upper bound for valid intersection distances along the ray.
For rendering hit, you need to get the lowest t
from the hittable objects along the ray.
Intersection_point = Ray_origin + t * Ray_direction
*/


//hit record
//clash: Hit point where the ray intersects the object's surface. 
//normal: Vector perpendicular to the surface at the point of intersection.
//distance: Ray(t) = Origin + t * Direction -> t in the formula
//front_face: true if the ray is outside the object 
typedef struct s_hitrecord
{
	t_vec3		clash;
	double		clash_distance;
	t_vec3		normal;
	t_rgb		color; //mozna netreba pokud obsahuje stejnou barvu jako *obj
	t_type		type;
	bool		front_face; //maybe discard, used for transparent
	t_object	*obj;
}				t_hitrecord;


#endif