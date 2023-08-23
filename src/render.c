/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:41:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/23 15:28:20 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

//HERE WE RENDER THE IMAGE AND PUTTING IT TO THE WINDOW OF MLX.

/*
Each pixel is 4 bytes, bpp = 32, line WIDTH*4
Writes the color components into the img_data buffer.
*/
void	put_pixels_to_img(t_scene *scene)
{
	int	y;
	int	x;
	int	index;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			index = y * scene->mlxdata->line_size + x * 4;
			scene->mlxdata->img_data[index] = scene->pixel_map[y][x].b;
			scene->mlxdata->img_data[index + 1] = scene->pixel_map[y][x].g;
			scene->mlxdata->img_data[index + 2] = scene->pixel_map[y][x].r;
			scene->mlxdata->img_data[index + 3] = (unsigned char)255;
			x++;
		}
		y++;
	}
}

void	ft_render(t_scene *scene)
{
	mlx_clear_window(scene->mlxdata->mlx_p, scene->mlxdata->win_p);
	put_pixels_to_img(scene);
	mlx_put_image_to_window(scene->mlxdata->mlx_p, scene->mlxdata->win_p,
		scene->mlxdata->img_p, 0, 0);
}
