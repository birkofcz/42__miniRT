/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:30:50 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:42:22 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
Counts the objects - sphere, plane or cylinder -
by the identifier in the description
 */
int	ft_count_objects(char **description, char *ident)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (description[i] != NULL)
	{
		if (ft_isstr(description[i], ident))
			count++;
		i++;
	}
	return (count);
}

int	ft_allocate_objects(t_scene *scene, char **description)
{
	scene->sphere_count = ft_count_objects(description, "sp");
	scene->plane_count = ft_count_objects(description, "pl");
	scene->cylinder_count = ft_count_objects(description, "cy");

	if ((scene->sphere_count + scene->plane_count + scene->cylinder_count) == 0)
		return (1);
	if (scene->sphere_count != 0)
		scene->sp = (t_sp *)malloc(sizeof(t_sp) * scene->sphere_count);
	else 
		scene->sp = NULL;
	if (scene->plane_count != 0)
		scene->pl = (t_pl *)malloc(sizeof(t_pl) * scene->plane_count);
	else
		scene->pl = NULL;
	if (scene->cylinder_count != 0)
		scene->cy = (t_cy *)malloc(sizeof(t_cy) * scene->cylinder_count);
	else
		scene->cy = NULL;
	return (0);
}
