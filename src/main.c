/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/21 15:45:27 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	init_pixel_map(t_scene *scene)
{
	t_rgb **temp_map;
	int		i;

	i = 0;
	temp_map = malloc(sizeof(t_rgb *) * HEIGHT);
	while (i < HEIGHT)
	{
		temp_map[i] = malloc(sizeof(t_rgb) * WIDTH);
		i++;
	}
	scene->pixel_map = temp_map;
}

void init_camera2(t_cam *camera)
{
	double half_width;
	t_vec3 tmp;
	t_vec3 vec_up;
	t_vec3	look_at;
	/*
vup typically stands for "view up" or "up direction" in the context of computer
graphics and rendering. It represents the direction that is considered to be
"up" from the camera's perspective. This vector is used to define the
orientation of the camera, specifically the camera's vertical direction,
within the scene. In a 3D scene, the concept of "up" is essential for
establishing the camera's orientation and ensuring that the rendered
image appears correctly aligned. The vup vector helps define how the
camera is tilted or rotated with respect to the world's vertical axis.*/
	
	// Set up the camera's properties

	vec_up = camera->normal;  // Up direction of the camera
	camera->fov_rad = camera->fov * M_PI / 180;  // Convert field of view to radians
	camera->focal_length = 1.0;  // Focal length (used for depth of field effects), distance between camera and viewport.
	look_at = create_vec3(0,0,0);
	// Calculate half width of the imaging plane
	half_width = camera->focal_length * tan(camera->fov_rad / 2);
		
	// Calculate viewport dimensions
	camera->viewport_height = 2.0 * half_width;
	camera->viewport_width = camera->aspect_ratio * camera->viewport_height;
		
	// Calculate camera's basis vectors
	camera->w = normalize_vector(substraction(camera->viewpoint, look_at));  // Forward direction
	//w = forward_direction_vector, This vector represents the direction in which the camera is looking.
	camera->u = normalize_vector(cross_product(vec_up, camera->w));
	// Right direction = represents the "right" direction from the camera's
	// perspective, perpendicular to both the camera's
	// forward direction (camera->w) and the "up" direction (vec_up).
	camera->v = cross_product(camera->w, camera->u);  // Up direction
	//This vector represents the "up" direction from the camera's perspective,
	//perpendicular to both the camera's forward direction (camera->w)
	//and the "right" direction (camera->u).
	/* vup is usually a user-defined vector that guides how the camera
	is oriented relative to the scene's "up," while camera->v is
	a calculated vector that ensures the camera's
	local "up" direction aligns with the orientation vectors w and u.*/
		
	// Calculate the horizontal and vertical vectors that define the imaging plane
	camera->horizontal = multiply(camera->u, camera->viewport_width);
	camera->vertical = multiply(camera->v, camera->viewport_height);
		
	// Calculate the lower left corner of the imaging plane
	tmp = multiply(camera->w, 1 / camera->focal_length);
	tmp = substraction(camera->viewpoint, tmp);
	tmp = substraction(tmp, multiply(camera->horizontal, 0.5));
	tmp = substraction(tmp, multiply(camera->vertical, 0.5));
	camera->lower_left_corner = tmp;
}

/*
Sending rays from the camera to every pixel of a projecting image.
The color of pixels is calculated and stored in pixel_map, which
is later used for rendering of the image.
*/
void	create_pix_matrix(t_scene *scene)
{
	int		x;
	int		y;
	t_rgb	pixel_color;

	//pixel_color = fill_rgb(0, 0, 0);
	init_camera2(&scene->cam);
	init_pixel_map(scene);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			scene->ray = calculate_ray(scene, x, y);
			pixel_color = ray_color(scene);			
            scene->pixel_map[y][x] = pixel_color;
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_mlxdata	mlxdata;

	if (argc == 1)
		return (ft_error("Missing scene file path"), 1);
	ft_parser(argv[1], &scene);
	create_pix_matrix(&scene);
	ft_init_mlx(&mlxdata);
	ft_init_image(&mlxdata);
	ft_render(&mlxdata, &scene);
	mlx_hook(mlxdata.win_p, EXIT_BUTTON, 0, ft_endgame, &mlxdata);
	//mlx_mouse_hook(mlxdata.win_p, ft_mouse_event, &mlxdata);
	mlx_key_hook(mlxdata.win_p, ft_key_event, &mlxdata);
	
	mlx_loop(mlxdata.mlx_p);
	return (0);
}
