/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/07 18:03:28 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

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
}

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

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_mlxdata	mlxdata;

	if (argc == 1)
		return (ft_error("Missing scene file path"), 1);
	ft_parser(argv[1], &scene);
	init_pixel_map(&scene);
	render_sphere(&scene);
	//
	//debug_all(&scene);
	ft_init_mlx(&mlxdata);
	ft_init_image(&mlxdata);
	ft_render(&mlxdata, &scene);
	mlx_hook(mlxdata.win_p, EXIT_BUTTON, 0, ft_endgame, &mlxdata);
	//mlx_mouse_hook(mlxdata.win_p, ft_mouse_event, &mlxdata);
	mlx_key_hook(mlxdata.win_p, ft_key_event, &mlxdata);
	mlx_loop(mlxdata.mlx_p);
	return (0);
}
