/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:22:24 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/21 14:16:49 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
	}
	free(split);
}

t_rgb	fill_rgb(int r, int g, int b)
{
	t_rgb	result;

	result.r = r;
	result.g = g;
	result.b = b;
	return (result);

void free_object_list(t_object *obj)
{
	t_sp *sphere;
	t_cy *cylinder;
	t_pl *plane;
	 t_object *next;

	sphere = NULL;
	cylinder = NULL;
	plane = NULL;
    while (obj != NULL)
    {
        next = obj->next;
        if (obj->type == SPHERE)
        {
            sphere = (t_sp *)obj->object;
            free(sphere);
        }
        else if (obj->type == CYLINDER)
        {
            cylinder = (t_cy *)obj->object;
            free(cylinder);
        }
        else if (obj->type == PLANE)
        {
            plane = (t_pl *)obj->object;
            free(plane);
        }
        free(obj);
        obj = next;
    }
}
