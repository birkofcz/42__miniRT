/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:53:34 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/24 15:01:58 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_object	*init_new_object(char *desc)
{
	t_object	*new_object;

	new_object = (t_object *)malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	if (ft_strncmp(desc, "sp", 2) == 0)
	{
		new_object->object = (void *)ft_init_sphere(desc);
		new_object->type = SPHERE;
	}
	else if (ft_strncmp(desc, "pl", 2) == 0)
	{
		new_object->object = (void *)ft_init_plane(desc);
		new_object->type = PLANE;
	}
	else if (ft_strncmp(desc, "cy", 2) == 0)
	{
		new_object->object = (void *)ft_init_cylinder(desc);
		new_object->type = CYLINDER;
	}
	if (!(new_object->object)) 
		return (free(new_object), NULL);
	new_object->next = NULL;
	return (new_object);
}

void	append_to_scene(t_scene *scene, t_object **current,
	t_object *new_object)
{
	if (*current == NULL) 
	{
		scene->head_object = new_object;
		*current = new_object;
	}
	else 
	{
		(*current)->next = new_object;
		*current = (*current)->next;
	}
}
