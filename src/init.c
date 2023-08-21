/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:35:14 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/12 18:59:03 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_init(char **description, t_scene *scene)
{
	if (!ft_init_env(description, scene))
		return (ft_error("Duplicate or missing A, C, L values"), 1);
	if (ft_count_objects (description) == 0)
		return (ft_error("No valid objects"), 1);
	ft_init_objects(description, scene);
	return (0);
}

void	ft_init_image(t_mlxdata *mlxdata)
{
	int		bpp;
	int		line_size;
	int		endian;
	char	*tmp;

	mlxdata->img_p = mlx_new_image(mlxdata->mlx_p, WIDTH, HEIGHT);
	if (!(mlxdata->img_p))
		ft_clean_exit(mlxdata);
	tmp = mlx_get_data_addr(mlxdata->img_p, &bpp, &line_size, &endian);
	mlxdata->bpp = bpp;
	mlxdata->line_size = line_size;
	//printf("bpp = %d, line_size = %d, endian = %d", bpp, line_size, endian);
	mlxdata->img_data = tmp;
}

void	ft_init_mlx(t_mlxdata *mlxdata)
{
	mlxdata->mlx_p = mlx_init();
	if (!mlxdata->mlx_p)
		ft_clean_exit(mlxdata);
	mlxdata->win_p = mlx_new_window(mlxdata->mlx_p, WIDTH, HEIGHT,
			"[TS]miniRT");
	if (!mlxdata->win_p)
		ft_clean_exit(mlxdata);
}
