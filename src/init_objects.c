/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:04:48 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/14 15:02:19 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_sp	*ft_init_sphere(char *line)
{
	t_sp	*sphere;
	char	**param;
	char	**coor;
	char	**rgb;

	sphere = (t_sp *)malloc(sizeof(t_sp)); 
	if (sphere == NULL)
	{
        // Handle memory allocation error
        return NULL;
    }
	param = ft_split(line, ' ');
	coor = ft_split(param[1], ',');
	sphere->center.x = ft_atof(coor[0]);
	sphere->center.y = ft_atof(coor[1]);
	sphere->center.z = ft_atof(coor[2]);
	ft_freesplit(coor);
	sphere->diameter = ft_atof(param[2]);
	rgb = ft_split(param[3], ',');
	sphere->color.r = ft_atoi(rgb[0]);
	sphere->color.g = ft_atoi(rgb[1]);
	sphere->color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (sphere);
}

t_pl	*ft_init_plane(char *line)
{
	t_pl	*plane;
	char	**param;
	char	**temp;
	char	**rgb;

	plane = (t_pl *)malloc(sizeof(t_pl)); 
    if (plane == NULL)
    {
        // Handle memory allocation error
        return NULL;
    }
	param = ft_split(line, ' ');
	temp = ft_split(param[1], ',');
	plane->point.x = ft_atof(temp[0]);
	plane->point.y = ft_atof(temp[1]);
	plane->point.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	temp = ft_split(param[2], ',');
	plane->normal.x = ft_atof(temp[0]);
	plane->normal.y = ft_atof(temp[1]);
	plane->normal.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	rgb = ft_split(param[3], ',');
	plane->color.r = ft_atoi(rgb[0]);
	plane->color.g = ft_atoi(rgb[1]);
	plane->color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (plane);
}

t_cy	*ft_init_cylinder(char *line)
{
	t_cy	*cylinder;
	char	**param;
	char	**temp;
	char	**rgb;

	cylinder = (t_cy *)malloc(sizeof(t_cy)); 
    if (cylinder == NULL)
    {
        // Handle memory allocation error
        return NULL;
    }
	param = ft_split(line, ' ');
	temp = ft_split(param[1], ',');
	cylinder->center.x = ft_atof(temp[0]);
	cylinder->center.y = ft_atof(temp[1]);
	cylinder->center.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	temp = ft_split(param[2], ',');
	cylinder->normal.x = ft_atof(temp[0]);
	cylinder->normal.y = ft_atof(temp[1]);
	cylinder->normal.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	cylinder->diameter = ft_atof(param[3]);
	cylinder->height = ft_atof(param[4]);
	rgb = ft_split(param[5], ',');
	cylinder->color.r = ft_atoi(rgb[0]);
	cylinder->color.g = ft_atoi(rgb[1]);
	cylinder->color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (cylinder);
}

void	ft_init_objects(char **description, t_scene *scene)
{
	int	i;
	t_object *current = NULL;
	t_object *new_object;

	i = 0;
	while (description[i])
	{
		if (ft_isstr(description[i], "sp") || ft_isstr(description[i], "pl")
			|| ft_isstr(description[i], "cy"))
		{
			new_object = (t_object *)malloc(sizeof(t_object));
			if (new_object == NULL)
			{
				return;//error
			}
			if (ft_strncmp(description[i], "sp", 2) == 0)
			{
				new_object->object = (void *)ft_init_sphere(description[i]);
				new_object->type = SPHERE;
			}
			else if (ft_strncmp(description[i], "pl", 2) == 0)
			{
				new_object->object = (void *) ft_init_plane(description[i]);
				new_object->type = PLANE;
			}
			else if (ft_strncmp(description[i], "cy", 2) == 0)
			{
				new_object->object = (void *) ft_init_cylinder(description[i]);
				new_object->type = CYLINDER;
			}
			new_object->next = NULL;
			if (current == NULL)
			{
				scene->head_object = new_object;
				current = new_object;
			}
			else
			{
				current->next = new_object;
				current = current->next;
			}
		}
		i++;
	}
	scene->object = scene->head_object;
}
