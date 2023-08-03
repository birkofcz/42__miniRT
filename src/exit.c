/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:32:08 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 17:14:33 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* 
Clean exit.
 */
void	ft_clean_exit(t_mlxdata *mlxdata) //add scene as second argument - clear also that struct
{
	if (!mlxdata)
		exit(0);
	if (mlxdata->img_p && mlxdata->mlx_p)
		mlx_destroy_image(mlxdata->mlx_p, mlxdata->img_p);
	if (mlxdata->win_p && mlxdata->mlx_p)
		mlx_destroy_window(mlxdata->mlx_p, mlxdata->win_p);
	if (mlxdata->mlx_p)
	{
		mlx_loop_end(mlxdata->mlx_p);
		mlx_destroy_display(mlxdata->mlx_p);
		free(mlxdata->mlx_p);
	}
	exit(0);
}

/* MLX takes int type funct, this needs to be here to call clean exit */
int	ft_endgame(t_mlxdata *mlxdata)
{
	ft_clean_exit(mlxdata);
	return (0);
}
