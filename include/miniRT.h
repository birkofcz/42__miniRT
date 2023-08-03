/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:04:05 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:41:08 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../mlx/mlx.h"
# include "objects.h"
# include <stdbool.h>

/* error.c */
void	ft_error(char *message);

/* init_objects.c */
void	ft_init_objects(char **description, t_scene *scene, char *ident);
t_cy	ft_init_cylinder(char *line);
t_pl	ft_init_plane(char *line);
t_sp	ft_init_sphere(char *line);

/* init_objects_utils.c */
int		ft_count_objects(char **description, char *ident);
int		ft_allocate_objects(t_scene *scene, char **description);

/* init_scene.c */
bool	ft_init_env(char **description, t_scene *scene);
int		ft_check_env(char *line);
t_light	init_light(char *line);
t_cam	init_camera(char *line);
t_amb	init_ambient(char *line);

/* init.c */
int		ft_init(char **description, t_scene *scene);

/* parser.c */
int		ft_parser(char *file, t_scene *scene);
bool	ft_testfile(char *input);

/* utils.c */
void	ft_freesplit(char **split);

/* debug.c */
void	debug_all(t_scene *scene);

#endif