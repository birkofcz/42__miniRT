/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:04:05 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/26 11:38:43 by sbenes           ###   ########.fr       */
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
void		ft_error(char *message);

/* events.c */
int			ft_key_event(int key, t_scene *scene);

/* exit.c */
int			ft_endgame(t_scene *scene);

/* hit_cylinder.c */
bool		hit_cylinder(t_scene *scene, t_hitrecord *rec, t_object *obj);
bool		hit_cylinder_top_cap(t_object *obj, t_hitrecord *rec, t_cy *c,
				t_ray *ray);
bool		hit_cylinder_bottom_cap(t_object *obj, t_hitrecord *rec, t_cy *c,
				t_ray *r);
bool		hit_cylinder_surface(t_object *obj, t_hitrecord *rec, t_cy 
				*cylinder, t_ray *ray);

/* hit_cylinder_utils.c */
void		quadratic_cylinder(t_cy *cylinder,	t_ray ray, t_quads *solution);
t_vec3		get_cylinder_normal(t_vec3 point, t_cy *cylinder);

/* hit_plane.c */
bool		hit_plane(t_scene *scene, t_hitrecord *rec, t_object *obj);

/* hit_sphere.c */
bool		hit_sphere(t_scene *scene, t_hitrecord *rec, t_object *obj);
t_vec3		get_sphere_normal(t_vec3 clash, t_sp *sphere);
t_quads		quadratic_sphere(t_vec3 center, double radius, t_ray r);

/* init_objects.c */
bool		ft_init_objects(char **description, t_scene *scene);
t_cy		*ft_init_cylinder(char *line);
t_pl		*ft_init_plane(char *line);
t_sp		*ft_init_sphere(char *line);
void		ft_freelist(t_scene *scene);

/* init_objects_utils.c */
int			ft_count_objects(char **description);
bool		ft_fillcyldiahei(t_cy *cyl, char *dia, char *hei);
void		ft_free_sp(char **data, char **param, t_sp *sphere,
				char *error_msg);
void		ft_free_pl(char **data, char **param, t_pl *plane, char *error_msg);
void		ft_free_cy(char **data, char **param, t_cy *cyl, char *error_msg);

/* init_object_utils2.c */
bool		ft_testparam(char *param);
bool		ft_fillcyldiahei(t_cy *cyl, char *dia, char *hei);
bool		ft_testcoors(char **coors);
bool		ft_testvector(char **vector);
bool		ft_testcolor(char **color);

/* init_object_utils3.c */
t_object	*init_new_object(char *desc);
void		append_to_scene(t_scene *scene, t_object **current,
				t_object *new_object);

/* init_scene.c */
bool		ft_init_env(char **description, t_scene *scene);
int			ft_check_env(char *line);
t_light		init_light(char *line, int *count, char **des);
t_cam		init_camera(char *line, int *count, char **des);
t_amb		init_ambient(char *line, int *count, char **des);

/* init_scene_utils.c */
void		ft_free_amb(char **data, char **param, char *error_msg, char **des);
void		ft_free_cam(char **data, char **param, char *error_msg, char **des);
void		ft_free_light(char **data, char **param, char *error_msg,
				char **des);
bool		ft_testratio(char *param);
bool		ft_testfov(char *param);

/* init.c */
int			ft_init(char **description, t_scene *scene);
void		ft_init_image(t_scene *scene, t_mlxdata *mlxdata);
void		ft_init_mlx(t_scene *scene, t_mlxdata *mlxdata);

/* light.c */
void		apply_light(t_scene *scene, t_hitrecord *rec);
void		calculate_and_apply_light(t_scene *scene, t_hitrecord *rec,
				bool shadow);
void		calculate_diffuse(t_scene *scene, t_hitrecord *rec, double dot);
t_rgb		apply_ambient_shadow(t_rgb object_color, t_amb amb);
t_rgb		apply_ambient(t_rgb object_color, t_amb amb);

/* light_utils.c */
double		ft_clamp(double value, double min, double max);
t_rgb		color_clamp(t_rgb color);
t_rgb		color_scalar(t_rgb color, double scalar);
t_rgb		calculate_sphere_diffuse(t_hitrecord *rec, t_scene *scene, 
				double dot);
t_rgb		calculate_cylinder_diffuse(t_hitrecord *rec, t_scene *scene, 
				t_vec3 light_normalized);

/* main.c */
void		create_pix_matrix(t_scene *scene);
void		init_camera2(t_cam *camera);
void		init_pixel_map(t_scene *scene);

/* parser.c */
int			ft_parser(char *file, t_scene *scene);
bool		ft_testfile(char *input);

/* ray.c */
bool		hit(t_scene *scene, t_hitrecord *rec, t_object *obj);
bool		hittable_list_hit(t_scene *scene, t_hitrecord *rec);
t_vec3		clash_point(t_ray *ray, double t);
t_ray		create_ray(t_vec3 origin, t_vec3 direction);
t_ray		calculate_ray(t_scene *scene, int x, int y);

/* ray_utils.c */
t_rgb		ray_color(t_scene *scene);
t_vec3		direction_vec_creation(t_scene *scene, double u, double v);

/* render.c */
void		ft_render(t_scene *scene);
void		put_pixels_to_img(t_scene *scene);

/* shadow.c */
bool		is_in_shadow(t_scene *scene, t_hitrecord *rec);
bool		cylinder_shadow(t_ray ray, t_cy *cylinder);
bool		check_top_intersection(t_ray *ray, t_cy *c);
bool		check_solution(t_ray *ray, t_cy *cylinder, double t, double *t_hit);

/* shadow_utils.c */
bool		sphere_shadow(t_ray ray, t_sp *sphere);

/* utils.c */
void		free_object_list(t_object *obj);
void		free_pixel_map(t_rgb **pixel_map);
void		ft_freesplit(char **split);
t_rgb		fill_rgb(int r, int g, int b);
int			ft_arraysize(char **array);


/* vector_operations.c */
t_vec3		create_vec3(double x, double y, double z);
t_vec3		normalize_vector(t_vec3 vector);
t_vec3		substraction(t_vec3 vec1, t_vec3 vec2);
t_vec3		addition(t_vec3 vec1, t_vec3 vec2);
t_vec3		multiply(t_vec3 vec1, double x);

/* vector_operations_utils.c */
t_vec3		cross_product(t_vec3 a, t_vec3 b);
double		dot_product(t_vec3 a, t_vec3 b);
double		vector_len(t_vec3 vector);
double		length_squared(t_vec3 v);
bool		is_normal_negative(t_vec3 vec);

#endif