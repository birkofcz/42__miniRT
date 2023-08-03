/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:35:14 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:35:42 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_init(char **description, t_scene *scene)
{
	if (!ft_init_env(description, scene))
		return (ft_error("Duplicate or missing A, C, L values"), 1);
	if (ft_allocate_objects(scene, description) == 1)
		return (ft_error("No valid objects"), 1);
	if (scene->sp != NULL)
		ft_init_objects(description, scene, "sp");
	if (scene->pl != NULL)
		ft_init_objects(description, scene, "pl");
	if (scene->cy != NULL)
		ft_init_objects(description, scene, "cy");
	return (0);
}