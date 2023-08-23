/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:04:05 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/23 14:02:07 by sbenes           ###   ########.fr       */
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
bool	ft_testcoors(char **coors);
bool	ft_testvector(char **vector);
bool	ft_testparam(char *param);
bool	ft_testcolor(char **color);


/* init_objects_utils.c */
int		ft_count_objects(char **description);
bool	ft_fillcyldiahei(t_cy *cyl, char *dia, char *hei);
void	ft_free_sp(char **data, char **param, t_sp *sphere, char *error_msg);
void	ft_free_pl(char **data, char **param, t_pl *plane, char *error_msg);
void	ft_free_cy(char **data, char **param, t_cy *cyl, char *error_msg);


/* init_object_utils2.c */
bool	ft_testparam(char *param);
bool	ft_fillcyldiahei(t_cy *cyl, char *dia, char *hei);
bool	ft_testcoors(char **coors);
bool	ft_testvector(char **vector);
bool	ft_testcolor(char **color);


/* init_scene.c */
bool	ft_init_env(char **description, t_scene *scene);
int		ft_check_env(char *line);
t_light	init_light(char *line, int *count, char **des);
t_cam	init_camera(char *line, int *count, char **des);
t_amb	init_ambient(char *line, int *count, char **des);

/* init_scene_utils.c */
void	ft_free_amb(char **data, char **param, char *error_msg, char **des);
void	ft_free_cam(char **data, char **param, char *error_msg, char **des);
void	ft_free_light(char **data, char **param, char *error_msg, char **des);
bool	ft_testratio(char *param);
bool	ft_testfov(char *param);


/* init.c */
int		ft_init(char **description, t_scene *scene);
void	ft_init_image(t_scene *scene, t_mlxdata *mlxdata);
void	ft_init_mlx(t_scene *scene, t_mlxdata *mlxdata);

/* parser.c */
int		ft_parser(char *file, t_scene *scene);
bool	ft_testfile(char *input);

/* utils.c */
void	ft_freesplit(char **split);
t_rgb	fill_rgb(int r, int g, int b);
void free_object_list(t_object *obj);
void free_pixel_map(t_rgb **pixel_map);

/* events.c */
int		ft_key_event(int key, t_scene *scene);

/* exit.c */
void	ft_clean_exit(t_mlxdata *mlxdata); //add scene as second argument - clear also that struct
int		ft_endgame(t_scene *scene);

/* render.c */
void	ft_render(t_scene *scene);
void	put_pixels_to_img(t_scene *scene);


/* debug.c */
void	debug_all(t_scene *scene);
void debug_print_ray(t_ray ray);


/* ray.c */
t_ray	create_ray(t_vec3 origin, t_vec3 direction);
bool	hit(t_scene *scene, t_hitrecord *rec, t_object *obj);
t_vec3	clash_point(t_ray *r, double t);
t_ray	calculate_ray(t_scene *scene, int x, int y);

/* sphere.c */
t_rgb	ray_color(t_scene *scene);
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
double	length_squared(t_vec3 v);
bool	is_normal_negative(t_vec3 vec);

/* shadow.c */
bool	is_in_shadow(t_scene *scene, t_hitrecord *rec);
bool	cylinder_shadow(t_ray ray, t_cy *cylinder);
bool	sphere_shadow(t_ray ray, t_sp *sphere);

bool	hit_plane(t_scene *scene, t_hitrecord *rec, t_object *obj);
bool	hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj);
void	quadratic_cylinder(t_cy *cylinder,	t_ray ray, t_quadratic_solution *solution);
void	apply_light(t_scene *scene, t_hitrecord *rec);
t_quadratic_solution quadratic_sphere(t_vec3 center, double radius, t_ray r);

#endif