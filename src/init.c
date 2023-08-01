/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:11:15 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/01 14:03:21 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"

t_amb	init_ambient(char *line)
{
	t_amb	amb;
	char	**param;
	char	**rgb;

	param = ft_split(line, " ");
	amb.ratio = ft_atof(param[1]);
	rgb = ft_split(param[2], ",");
	ft_freesplit(param);
	amb.r = ft_atoi(rgb[0]);
	amb.g = ft_atoi(rgb[1]);
	amb.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	return (amb);
}

t_cam	init_camera(char *line)
{
	t_cam	cam;
	char	**param;
	char	**view_point;
	char	**orient_vect;

	param = ft_split(line, " ");
	view_point = ft_split(param[1], ",");
	cam.x = ft_atof(view_point[0]);
	cam.y = ft_atof(view_point[1]);
	cam.z = ft_atof(view_point[2]);
	ft_freesplit(view_point);
	orient_vect = ft_split(param[2], ",");
	cam.vx = ft_atof(orient_vect[0]);
	cam.vy = ft_atof(orient_vect[1]);
	cam.vz = ft_atof(orient_vect[2]);
	ft_freesplit(orient_vect);
	cam.fov = ft_atoi(param[3]);
	ft_freesplit(param);
	return (cam);
}

t_light	init_light(char *line)
{
	t_light	light;
	char	**param;
	char	**coor;

	param = ft_split(line, " ");
	coor = ft_split(param[1], ",");
	light.x = ft_atof(coor[0]);
	light.y = ft_atof(coor[1]);
	light.z = ft_atof(coor[2]);
	ft_freesplit(coor);
	light.bright_ratio = ft_atof(param[2]);
	ft_freesplit(param);
	return (light);
}

int	ft_check_env(char *line)
{
	int	i;

	i = 0;
	while (line[i] == " ")
		i++;
	if (line[i] == "A")
		return (1);
	else if (line[i] == "C")
		return (2);
	else if (line[i] == "L")
		return (3);
	else
		return (4);
}

bool	ft_init_env(char **description, t_scene *scene)
{
	int	i;
	int	env_count;

	i = 0;
	env_count = 0;
	scene->amb = NULL;
	scene->cam = NULL;
	scene->light = NULL;
	while (description[i] != NULL)
	{
		if (ft_check_env(description[i]) == 1)
		{
			scene->amb = init_ambient(description[i]);
			env_count++;
		}
		else if (ft_check_env(description[i]) == 2)
		{
			scene->cam = init_camera(description[i]);
			env_count++;
		}
		else if (ft_check_env(description[i]) == 3)
		{
			scene->light = init_light(description[i]);
			env_count++;
		}
		i++;
	}
	if (env_count != 3)
		return (false);
	return (true);
}

t_scene	*ft_init(char **description)
{
	t_scene	scene;
	int obj_count;

	obj_count = 0;
	if (!ft_init_env(description, &scene))
		return (ft_error("Duplicate A, C, L values"), NULL);
	obj_count += ft_init_sphere(description, &scene);
	obj_count += ft_init_plane(description, &scene);
	obj_count += ft_init_cylinder(description, &scene);
	if (obj_count == 0)
		return (ft_error("No valid object."), NULL);
	return (&scene);
}