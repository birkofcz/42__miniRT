/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:57:33 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/03 15:21:29 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void print_ambient_light(const t_amb *ambient_light)
{
    printf("Ambient Light:\n");
    printf("Ratio: %f\n", ambient_light->ratio);
    printf("RGB: %d, %d, %d\n", ambient_light->r, ambient_light->g, ambient_light->b);
}

void print_camera(const t_cam *camera)
{
    printf("Camera:\n");
    printf("Position: (%f, %f, %f)\n", camera->x, camera->y, camera->z);
    printf("Orientation Vector: (%f, %f, %f)\n", camera->vx, camera->vy, camera->vz);
    printf("FOV: %d\n", camera->fov);
}

void print_light(const t_light *light)
{
    printf("Light:\n");
    printf("Position: (%f, %f, %f)\n", light->x, light->y, light->z);
    printf("Brightness Ratio: %f\n", light->bright_ratio);
}

void print_sphere(const t_sp *sphere)
{
    printf("Sphere:\n");
    printf("Center: (%f, %f, %f)\n", sphere->x, sphere->y, sphere->z);
    printf("Diameter: %f\n", sphere->diameter);
    printf("RGB: %d, %d, %d\n", sphere->r, sphere->g, sphere->b);
}

void print_plane(const t_pl *plane)
{
    printf("Plane:\n");
    printf("Point: (%f, %f, %f)\n", plane->x, plane->y, plane->z);
    printf("Normal Vector: (%f, %f, %f)\n", plane->vx, plane->vy, plane->vz);
    printf("RGB: %d, %d, %d\n", plane->r, plane->g, plane->b);
}

void print_cylinder(const t_cy *cylinder)
{
    printf("Cylinder:\n");
    printf("Center: (%f, %f, %f)\n", cylinder->x, cylinder->y, cylinder->z);
    printf("Axis Vector: (%f, %f, %f)\n", cylinder->vx, cylinder->vy, cylinder->vz);
    printf("Diameter: %f\n", cylinder->diameter);
    printf("Height: %f\n", cylinder->height);
    printf("RGB: %d, %d, %d\n", cylinder->r, cylinder->g, cylinder->b);
}

void	debug_all(t_scene * scene)
{
    print_ambient_light(&scene->amb);
	printf("\n");
    print_camera(&scene->cam);
	printf("\n");
    print_light(&scene->light);
	printf("\n");
    // Print sphere, plane, and cylinder values if they are not NULL
    if (scene->sp != NULL)
    {
        for (int i = 0; i < scene->sphere_count; i++) // 'num_spheres' is the number of spheres in the array
        {
            print_sphere(&scene->sp[i]);
        }
    }
	printf("\n");
    // Print planes if they are not NULL
    if (scene->pl != NULL)
    {
        for (int i = 0; i < scene->plane_count; i++) // 'num_planes' is the number of planes in the array
        {
            print_plane(&scene->pl[i]);
        }
    }
	printf("\n");
    // Print cylinders if they are not NULL
    if (scene->cy != NULL)
    {
        for (int i = 0; i < scene->cylinder_count; i++) // 'num_cylinders' is the number of cylinders in the array
        {
            print_cylinder(&scene->cy[i]);
        }
    }
}

void ft_print_split(char **split)
{
	int i = 0;
	while (split[i])
	{
        printf("description[%d] :%s\n",i, split[i]);
		i++;
    }
}