/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/14 15:09:04 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
/*
int render_sphere(t_scene *scene)
{
    // Image
    const int image_width = WIDTH;
    const int image_height = HEIGHT;
	const double aspect_ratio = image_width / image_height;

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    t_vec3 origin = scene->cam.viewpoint;
    t_vec3 horizontal = {viewport_width, 0, 0};
    t_vec3 vertical = {0, viewport_height, 0};
    t_vec3 lower_left_corner = substraction(origin, multiply(addition(horizontal, vertical), 0.5));
    lower_left_corner = substraction(lower_left_corner, multiply((t_vec3){0, 0, 1}, focal_length));

    for (int j = image_height - 1; j >= 0; --j)
	{
        fprintf(stderr, "\rScanlines remaining: %d ", j);
        for (int i = 0; i < image_width; ++i) {
            double u = (double)i / (image_width - 1);
            double v = (double)j / (image_height - 1);
			t_vec3 direction = substraction(addition(addition(lower_left_corner, multiply(horizontal, u)), multiply(vertical, v)), origin);
            t_ray ray = create_ray(origin, direction);
			t_rgb pixel_color = ray_color(ray, scene);
            scene->pixel_map[j][i] = pixel_color;
        }
    }

    fprintf(stderr, "\nDone.\n");
    return 0;
}*/
/*
t_ray	ray_for_pixel(t_scene *scene, float px, float py)
{
	float		world_x;
	float		world_y;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	world_x = camera->half_width - (px + 0.5) * camera->pixel_size;
	world_y = camera->half_height - (py + 0.5) * camera->pixel_size;
	pixel = multiply_tp_mx(camera->inverse, point(world_x, world_y, -1));
	origin = multiply_tp_mx(camera->inverse, point(0, 0, 0));
	direction = normalize(subtract(pixel, origin));
	return (new_ray(origin, direction));
}

void	send_rays(t_scene *scene)
{
	float		x;
	float		y;
	t_ray		ray;
	t_rgb	color;
	t_cam	camera;

	y = 0;
	while (y < HEIGHT- 1)
	{
		x = 0;
		while (x < WEIGHT - 1)
		{
			ray = ray_for_pixel(scene, x, y);
			color = color_at(scene->world, ray);
			write_pixel(canvas, x, y, rgb(color));
			x++;
		}
		y++;
	}
}
*/
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

t_vec3	direction_vec_creation(t_scene *scene, double u, double v)
{
	t_vec3 horizontal_contribution;
	t_vec3 vertical_contribution;
	t_vec3 horizontal_sum;
	t_vec3 horizontal_and_vertical_sum;

	horizontal_contribution = multiply(scene->cam.horizontal, u);
	vertical_contribution = multiply(scene->cam.vertical, v);
	horizontal_sum = addition(scene->cam.lower_left_corner, horizontal_contribution);
	horizontal_and_vertical_sum = addition(horizontal_sum, vertical_contribution);
	return(substraction(horizontal_and_vertical_sum, scene->cam.viewpoint));
}

t_ray	calculate_ray(t_scene *scene, int x, int y)
{

    double u;
	double v;
	t_vec3	direction;
	printf("x = %d, y = %d\n", x, y);

 	u = (x + 0.5) / WIDTH;     // Adding 0.5 for single-sample center of pixel
    v = (HEIGHT - y - 0.5) / HEIGHT; 
	printf("u = %f, v = %f\n", u, v);
	direction = direction_vec_creation(scene, u, v);
	return(create_ray(scene->cam.viewpoint, direction));
}
//zalezi jestli zaciname od pixelu 1/1 a ne 0/0.

void	render(t_scene *scene)
{
	int		x;
	int		y;
	t_rgb	pixel_color;

	//pixel_color = fill_color(0, 0, 0);//dodelat
	init_camera2(&scene->cam);
	init_pixel_map(scene);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			scene->ray = calculate_ray(scene, x, y);
			
			//debug_print_ray(ray);
			pixel_color = ray_color2(scene);
			
            scene->pixel_map[y][x] = pixel_color;
			//av_color(&pixel_color, ray_color(data));
			//my_mlx_pixel_put(&data->img, x, y, rgb(pixel_color));
			x++;
		}
		y++;
	}
	//mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_mlxdata	mlxdata;

	if (argc == 1)
		return (ft_error("Missing scene file path"), 1);
	ft_parser(argv[1], &scene);
	//debug_all(&scene);	
	//send_rays(&scene);
	render(&scene);
	//
	
	ft_init_mlx(&mlxdata);
	ft_init_image(&mlxdata);
	ft_render(&mlxdata, &scene);
	mlx_hook(mlxdata.win_p, EXIT_BUTTON, 0, ft_endgame, &mlxdata);
	//mlx_mouse_hook(mlxdata.win_p, ft_mouse_event, &mlxdata);
	mlx_key_hook(mlxdata.win_p, ft_key_event, &mlxdata);
	
	mlx_loop(mlxdata.mlx_p);
	return (0);
}
