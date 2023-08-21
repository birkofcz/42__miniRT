/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:04:05 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/21 15:05:52 by sbenes           ###   ########.fr       */
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

# define WIDTH 1024
# define HEIGHT 576
# define EPSILON 1e-6

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
bool	ft_init_objects(char **description, t_scene *scene);
t_cy	*ft_init_cylinder(char *line);
t_pl	*ft_init_plane(char *line);
t_sp	*ft_init_sphere(char *line);

/* init_objects_utils.c */
int		ft_count_objects(char **description);
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
t_rgb	fill_rgb(int r, int g, int b);


/* events.c */
int		ft_key_event(int key, t_mlxdata *mlxdata);

/* exit.c */
void	ft_clean_exit(t_mlxdata *mlxdata); //add scene as second argument - clear also that struct
int		ft_endgame(t_mlxdata *mlxdata);

/* render.c */
void	ft_render(t_mlxdata *mlxdata, t_scene *scene);


/* debug.c */
void	debug_all(t_scene *scene);
void debug_print_ray(t_ray ray);


/* ray.c */
t_ray	create_ray(t_vec3 origin, t_vec3 direction);
bool	hit(t_scene *scene, t_hitrecord *rec, t_object *obj);
t_vec3	clash_point(t_ray *r, double t);

/* sphere.c */
t_rgb ray_color(t_ray ray, t_scene *scene);
t_rgb	ray_color2(t_scene *scene);
bool	hit_sphere(t_scene *scene, t_hitrecord *rec, t_object *obj);

/* vector_operations.c */
t_vec3	create_vec3(double x, double y, double z);
t_vec3	normalize_vector(t_vec3 vector);
double	vector_len(t_vec3 vector);
t_vec3	cross_product(t_vec3 a, t_vec3 b);
double	dot_product(t_vec3 a, t_vec3 b);
t_vec3	substraction(t_vec3 vec1, t_vec3 vec2);
t_vec3	addition(t_vec3 vec1, t_vec3 vec2);
t_vec3	multiply(t_vec3 vec1, double x);
double length_squared(t_vec3 v);

bool	hit_plane(t_scene *scene, t_hitrecord *rec, t_object *obj);
bool hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj);
void		quadratic_cylinder(t_cy *cylinder,	t_ray ray, t_quadratic_solution *solution);
void	apply_light(t_scene *scene, t_hitrecord *rec);
t_quadratic_solution quadratic_sphere(t_vec3 center, double radius, t_ray r);

/*zkopirovano, nutno upravit*/
void		print_mat4(t_mat4 mat);
t_mat4		mat4_identity(void);
t_mat4		mat4_mult(t_mat4 a, t_mat4 b);
t_mat4		mat4_translate(t_vec3 v);
t_mat4		mat4_scale(t_vec3 v);
t_mat4		mat4_rotate_x(double angle);
t_mat4		mat4_rotate_y(double angle);
t_mat4		mat4_rotate_z(double angle);
t_mat4		mat4_rotate(t_vec3 v);
t_mat4		mat4_transpose(t_mat4 m);
t_mat4		mat4_inverse(t_mat4 m);
t_vec3		mat4_mult_vect(t_mat4 m, t_vec3 v);
#endif