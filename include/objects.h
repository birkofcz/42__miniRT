/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:29:56 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/31 14:47:49 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

/* Ambient lightning
identifier: A
ratio - ambient lightning ratio in range [0.0,1.0]
rgb - colors in range [0-255] 
*/
typedef struct s_ambientlight
{
	float	ratio;
	int		r;
	int		g;
	int		b;
}	t_amb;

/* Camera 
identifier: C
xyz coordinates of the viewpoint
vx,vy,vz - 3d normalized orientation vector for each axis
fov - horizontal field of view in degrees in range [0,180]
 */
typedef struct s_camera
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		fov;
}	t_cam;

/* Light
identifier: L
xyz - coordinates of the lightpoint
bright_ratio - light brightness ratio in range [0.0,1.0]
 */
typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	bright_ratio;
}	t_light;

/* Sphere - object
identifier: sp
xyz - coordinates of the sphere center
diameter - the sphere diameter
rgb - rgb colors in range [0-255]
 */
typedef struct s_sphere
{
	float	x;
	float	y;
	float	z;
	float	diameter;
	int		r;
	int		g;
	int		b;
}	t_sp;

/* Plane - object
identifier: pl
xyz - coordinates of the point in the plane
vx,vy,vz - 3d normalized normal vector. In range [-1,1] for each axis
rgb - colors in range [0-255]
 */
typedef struct s_plane
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		r;
	int		g;
	int		b;
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
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	diameter;
	float	height;
	int		r;
	int		g;
	int		b;
}	t_cy;

#endif

