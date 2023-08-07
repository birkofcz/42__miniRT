/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:41:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/07 18:19:21 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//HERE WE RENDER THE IMAGE AND PUTTING IT TO THE WINDOW OF MLX.
// this function will be called every time we need to re-render - must get the data it needs

void put_pixels_to_img(t_mlxdata *mlxdata, t_scene *scene)
{
	int y;
	int x;

	int img_width = WIDTH;
	int img_height = HEIGHT;
	y = 0;
	while (y < img_height)
	{
		x = 0;
		while (x < img_width)
		{
			int index = y * mlxdata->line_size + x * 4; // Each pixel is 4 bytes, bpp = 32, line WIDTH*4

			// Write the color components into the img_data buffer
			mlxdata->img_data[index] = scene->pixel_map[y][x].b;
			mlxdata->img_data[index + 1] = scene->pixel_map[y][x].g;
			mlxdata->img_data[index + 2] = scene->pixel_map[y][x].r;
			mlxdata->img_data[index + 3] = (unsigned char)5;

			x++;
		}
		y++;
	}
}

void	ft_render(t_mlxdata *mlxdata, t_scene *scene)
{
	mlx_clear_window(mlxdata->mlx_p, mlxdata->win_p);

	put_pixels_to_img(mlxdata, scene);
	mlx_put_image_to_window(mlxdata->mlx_p, mlxdata->win_p, mlxdata->img_p, 0, 0);
	//ft_put_legend(mlxdata);
}


