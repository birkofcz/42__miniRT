/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:04:05 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/06 17:47:25 by tkajanek         ###   ########.fr       */
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

# define WIDTH 1000
# define HEIGHT 1000

/* Keymap for mlx loop */
enum e_keymap
{
	EXIT_BUTTON = 17,
	KEY_ESC = 65307,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_PLUS = 61,
	KEY_MINUS = 45,
	KEY_C = 99,
	KEY_S = 115,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	MOUSE_LCLICK = 1,
	MOUSE_ZOOMIN = 4,
	MOUSE_ZOOMOUT = 5
};

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
void	ft_init_image(t_mlxdata *mlxdata);
void	ft_init_mlx(t_mlxdata *mlxdata);

/* parser.c */
int		ft_parser(char *file, t_scene *scene);
bool	ft_testfile(char *input);

/* utils.c */
void	ft_freesplit(char **split);

/* events.c */
int		ft_key_event(int key, t_mlxdata *mlxdata);

/* exit.c */
void	ft_clean_exit(t_mlxdata *mlxdata); //add scene as second argument - clear also that struct
int		ft_endgame(t_mlxdata *mlxdata);

/* render.c */
void	ft_render(t_mlxdata *mlxdata);


/* debug.c */
void	debug_all(t_scene *scene);


/* ray.c */
t_ray	create_ray(t_vec3 origin, t_vec3 direction);

/* sphere.c */
t_rgb ray_color(t_ray ray, t_scene *scene);

/* vector_operations.c */
t_vec3	create_vec3(double x, double y, double z);
t_vec3	normalize_vector(t_vec3 vector);
double	vector_len(t_vec3 vector);
t_vec3	cross_product(t_vec3 a, t_vec3 b);
double	dot_product(t_vec3 a, t_vec3 b);
t_vec3	substraction(t_vec3 vec1, t_vec3 vec2);
t_vec3	addition(t_vec3 vec1, t_vec3 vec2);
t_vec3	multiply(t_vec3 vec1, double x);

#endif