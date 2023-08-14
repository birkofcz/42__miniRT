/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:11:15 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/09 17:55:13 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"

t_amb	init_ambient(char *line)
{
	t_amb	amb;
	char	**param;
	char	**rgb;

	param = ft_split(line, ' ');
	amb.ratio = ft_atof(param[1]);
	rgb = ft_split(param[2], ',');
	ft_freesplit(param);
	amb.color.r = ft_atoi(rgb[0]);
	amb.color.g = ft_atoi(rgb[1]);
	amb.color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	return (amb);
}

t_cam	init_camera(char *line)
{
	t_cam	cam;
	char	**param;
	char	**view_point;
	char	**orient_vect;

	param = ft_split(line, ' ');
	view_point = ft_split(param[1], ',');
	cam.viewpoint.x = ft_atof(view_point[0]);
	cam.viewpoint.y = ft_atof(view_point[1]);
	cam.viewpoint.z = ft_atof(view_point[2]);
	ft_freesplit(view_point);
	orient_vect = ft_split(param[2], ',');
	cam.normal.x = ft_atof(orient_vect[0]);
	cam.normal.y = ft_atof(orient_vect[1]);
	cam.normal.z = ft_atof(orient_vect[2]);
	ft_freesplit(orient_vect);
	cam.fov = ft_atoi(param[3]);
	ft_freesplit(param);
	cam.aspect_ratio = (double)16 / 9;
	return (cam);
}

t_light	init_light(char *line)
{
	t_light	light;
	char	**param;
	char	**coor;

	param = ft_split(line, ' ');
	coor = ft_split(param[1], ',');
	light.lightpoint.x = ft_atof(coor[0]);
	light.lightpoint.y = ft_atof(coor[1]);
	light.lightpoint.z = ft_atof(coor[2]);
	ft_freesplit(coor);
	light.bright_ratio = ft_atof(param[2]);
	ft_freesplit(param);
	return (light);
}

int	ft_check_env(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'A')
		return (1);
	else if (line[i] == 'C')
		return (2);
	else if (line[i] == 'L')
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
