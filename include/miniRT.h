/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:04:05 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/02 15:19:13 by tkajanek         ###   ########.fr       */
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

void	ft_error(char *message);
int	ft_parser(char *scene);
void	ft_freesplit(char **split);

/* init.c */
t_scene *ft_init(char **description);

/* init_objects.c */
void	ft_init_object(char **description, t_scene *scene, char *ident);
int	ft_allocate_objects(t_scene *scene, char **description);
#endif