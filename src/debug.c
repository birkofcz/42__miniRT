/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:57:33 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/14 14:46:34 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void debug_print_ray(t_ray ray) {
    printf("Ray Origin: (%.2f, %.2f, %.2f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Ray Direction: (%.2f, %.2f, %.2f)\n", ray.direction.x, ray.direction.y, ray.direction.z);
}


void print_ambient_light(const t_amb *ambient_light)
{
    printf("Ambient Light:\n");
    printf("Ratio: %f\n", ambient_light->ratio);
    printf("RGB: %d, %d, %d\n", ambient_light->color.r, ambient_light->color.g, ambient_light->color.b);
}

void print_camera(const t_cam *camera)
{
	printf("Camera:\n");
   printf("Viewpoint: (%.2f, %.2f, %.2f)\n", camera->viewpoint.x, camera->viewpoint.y, camera->viewpoint.z);
    printf("Normal: (%.2f, %.2f, %.2f)\n", camera->normal.x, camera->normal.y, camera->normal.z);
    printf("w: (%.2f, %.2f, %.2f)\n", camera->w.x, camera->w.y, camera->w.z);
    printf("u: (%.2f, %.2f, %.2f)\n", camera->u.x, camera->u.y, camera->u.z);
    printf("v: (%.2f, %.2f, %.2f)\n", camera->v.x, camera->v.y, camera->v.z);
    printf("Horizontal: (%.2f, %.2f, %.2f)\n", camera->horizontal.x, camera->horizontal.y, camera->horizontal.z);
    printf("Vertical: (%.2f, %.2f, %.2f)\n", camera->vertical.x, camera->vertical.y, camera->vertical.z);
    printf("Lower Left Corner: (%.2f, %.2f, %.2f)\n", camera->lower_left_corner.x, camera->lower_left_corner.y, camera->lower_left_corner.z);
    printf("FOV: %.2f\n", camera->fov);
    printf("FOV Rad: %.2f\n", camera->fov_rad);
    printf("Focal Length: %.2f\n", camera->focal_length);
    printf("Viewport Height: %.2f\n", camera->viewport_height);
    printf("Viewport Width: %.2f\n", camera->viewport_width);
    printf("Aspect Ratio: %.2f\n", camera->aspect_ratio);
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
    
	t_object *current = scene->head_object; // Start iterating from the head_object

    while (current != NULL)
    {
        if (current->type == SPHERE)
        {
            print_sphere((t_sp *)current->object);
        }
        else if (current->type == PLANE)
        {
            print_plane((t_pl *)current->object);
        }
        else if (current->type == CYLINDER)
        {
            print_cylinder((t_cy *)current->object);
        }
		printf("object printed, the next: %p\n", current->next);
        current = current->next; // Move to the next object in the linked list
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