/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:41:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 17:17:49 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//HERE WE RENDER THE IMAGE AND PUTTING IT TO THE WINDOW OF MLX.
// this function will be called every time we need to re-render - must get the data it needs

void	ft_render(t_mlxdata *mlxdata)
{
	mlx_clear_window(mlxdata->mlx_p, mlxdata->win_p);
	
	char *str = "TEST";
	int x = WIDTH / 2;
	int y = HEIGHT / 2;

	mlx_put_image_to_window(mlxdata->mlx_p, mlxdata->win_p, mlxdata->img_p, 0, 0);
	mlx_string_put(mlxdata->mlx_p, mlxdata->win_p, x, y, 0xFFFFFF, str);
	//ft_put_legend(mlxdata);
}


