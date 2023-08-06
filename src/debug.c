/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:57:33 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/06 15:49:52 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void print_ambient_light(const t_amb *ambient_light)
{
    printf("Ambient Light:\n");
    printf("Ratio: %f\n", ambient_light->ratio);
    printf("RGB: %d, %d, %d\n", ambient_light->color.r, ambient_light->color.g, ambient_light->color.b);
}

void print_camera(const t_cam *camera)
{
    printf("Camera:\n");
    printf("Position: (%f, %f, %f)\n", camera->viewpoint.x, camera->viewpoint.y, camera->viewpoint.z);
    printf("Orientation Vector: (%f, %f, %f)\n", camera->normal.x, camera->normal.y, camera->normal.z);
    printf("FOV: %d\n", camera->fov);
}

void print_light(const t_light *light)
{
    printf("Light:\n");
    printf("Position: (%f, %f, %f)\n", light->lightpoint.x, light->lightpoint.y, light->lightpoint.z);
    printf("Brightness Ratio: %f\n", light->bright_ratio);
}

void print_sphere(const t_sp *sphere)
{
    printf("Sphere:\n");
    printf("Center: (%f, %f, %f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
    printf("Diameter: %f\n", sphere->diameter);
    printf("RGB: %d, %d, %d\n", sphere->color.r, sphere->color.g, sphere->color.b);
}

void print_plane(const t_pl *plane)
{
    printf("Plane:\n");
    printf("Point: (%f, %f, %f)\n", plane->point.x, plane->point.y, plane->point.z);
    printf("Normal Vector: (%f, %f, %f)\n", plane->normal.x, plane->normal.y, plane->normal.z);
    printf("RGB: %d, %d, %d\n", plane->color.r, plane->color.g, plane->color.b);
}

void print_cylinder(const t_cy *cylinder)
{
    printf("Cylinder:\n");
    printf("Center: (%f, %f, %f)\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
    printf("Axis Vector: (%f, %f, %f)\n", cylinder->normal.x, cylinder->normal.y, cylinder->normal.z);
    printf("Diameter: %f\n", cylinder->diameter);
    printf("Height: %f\n", cylinder->height);
    printf("RGB: %d, %d, %d\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
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