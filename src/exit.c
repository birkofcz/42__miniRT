/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:32:08 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/22 17:18:43 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* MLX takes int type funct, this needs to be here to call clean exit */
int	ft_endgame(t_scene *scene)
{
	if (scene->mlxdata == NULL)
		exit(EXIT_SUCCESS);
	if (scene->mlxdata->img_p != NULL && scene->mlxdata->mlx_p != NULL)
		mlx_destroy_image(scene->mlxdata->mlx_p, scene->mlxdata->img_p);
	if (scene->mlxdata->win_p != NULL && scene->mlxdata->mlx_p != NULL)
		mlx_destroy_window(scene->mlxdata->mlx_p, scene->mlxdata->win_p);
	if (scene->mlxdata->mlx_p != NULL )
	{
		mlx_loop_end(scene->mlxdata->mlx_p);
		mlx_destroy_display(scene->mlxdata->mlx_p);
		free(scene->mlxdata->mlx_p);
	}
	if (scene != NULL)
	{
		if (scene->head_object != NULL)
			free_object_list(scene->head_object);
		if (scene->pixel_map != NULL)
			free_pixel_map(scene->pixel_map);
	}
	exit(EXIT_SUCCESS);
}
