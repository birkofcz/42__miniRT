/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 17:23:51 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_mlxdata	mlxdata;

	if (argc == 1)
		return (ft_error("Missing scene file path"), 1);
	ft_parser(argv[1], &scene);
	debug_all(&scene);
	ft_init_mlx(&mlxdata);
	ft_init_image(&mlxdata);
	ft_render(&mlxdata);
	mlx_hook(mlxdata.win_p, EXIT_BUTTON, 0, ft_endgame, &mlxdata);
	//mlx_mouse_hook(mlxdata.win_p, ft_mouse_event, &mlxdata);
	mlx_key_hook(mlxdata.win_p, ft_key_event, &mlxdata);
	mlx_loop(mlxdata.mlx_p);
	return (0);
}
