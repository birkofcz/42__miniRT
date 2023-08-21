/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:11:15 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/21 17:26:51 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"

static void	ft_free_amb(char **data, char **param, t_amb *amb, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_error(error_msg);
	amb->error_flag = true;
	exit(1);
}

static void	ft_free_cam(char **data, char **param, t_cam *cam, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_error(error_msg);
	exit(1);
}

static void	ft_free_light(char **data, char **param, t_light *light, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_error(error_msg);
	exit(1);
}

/* Functions */
t_amb	init_ambient(char *line)
{
	t_amb	amb;
	char	**param;
	char	**rgb;

	param = ft_split(line, ' ');
	if (ft_testparam(param[1]))
		amb.ratio = ft_atof(param[1]);
	else
		ft_free_amb(NULL, param, &amb, "Bad ambient ratio");
	rgb = ft_split(param[2], ',');
	if (ft_testcolor(rgb))
		amb.color = fill_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		ft_free_amb(rgb, param, &amb, "Bad coloring in ambient");
	ft_freesplit(param);
	ft_freesplit(rgb);
	return (amb);
}

t_cam	init_camera(char *line)
{
	t_cam	cam;
	char	**param;
	char	**v;
	char	**n;

	param = ft_split(line, ' ');
	v = ft_split(param[1], ',');
	if (ft_testcoors(v))
		cam.viewp = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, &cam, "Bad viewpoint data");
	ft_freesplit(v);
	n = ft_split(param[2], ',');
	if (ft_testvector(n))
		cam.normal = create_vec3(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	else
		ft_free_cam(n, param, &cam, "Invalid orient vector");
	ft_freesplit(n);
	if (ft_testparam(param[3]))
		cam.fov = ft_atoi(param[3]);
	else
		ft_free_cam(NULL, param, &cam, "Invalid FOV");
	ft_freesplit(param);
	cam.aspect_ratio = (double)16 / 9;
	return (cam);
}

t_light	init_light(char *line)
{
	t_light	light;
	char	**param;
	char	**lp;

	param = ft_split(line, ' ');
	lp = ft_split(param[1], ',');
	if (ft_testcoors(lp))
		light.lightpoint = create_vec3(ft_atof(lp[0]), ft_atof(lp[1]),
				ft_atoi(lp[2]));
	else
		ft_free_light(lp, param, &light, "Bad viewpoint data");
	ft_freesplit(lp);
	if (ft_testparam(param[2]))
		light.bright_ratio = ft_atof(param[2]);
	else
		ft_free_light(NULL, param, &light, "Bad brightness ratio");
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
			scene->amb = init_ambient(description[i]); //do teto funkce free(description) --pred exit!
			env_count++;
		}
		else if (ft_check_env(description[i]) == 2)
		{
			scene->cam = init_camera(description[i]); //do teto funkce free(description) --pred exit!
			env_count++;
		}
		else if (ft_check_env(description[i]) == 3)
		{
			scene->light = init_light(description[i]); //do teto funkce free(description) --pred exit!
			env_count++;
		}
		i++;
	}
	if (env_count != 3)
		return (ft_error("Duplicate or missing A, C, L values"), false);
	return (true);
}
