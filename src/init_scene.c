/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:11:15 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/23 15:02:43 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"

t_amb	init_ambient(char *line, int *count, char **des)
{
	t_amb	amb;
	char	**param;
	char	**rgb;

	param = ft_split(line, ' ');
	if (ft_testratio(param[1]))
		amb.ratio = ft_atof(param[1]);
	else
		ft_free_amb(NULL, param, "Bad ambient ratio", des);
	rgb = ft_split(param[2], ',');
	if (ft_testcolor(rgb))
		amb.color = fill_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		ft_free_amb(rgb, param, "Bad coloring in ambient", des);
	ft_freesplit(param);
	ft_freesplit(rgb);
	*count += 1;
	return (amb);
}

t_cam	init_camera(char *line, int *count, char **des)
{
	t_cam	cam;
	char	**param;
	char	**v;

	param = ft_split(line, ' ');
	v = ft_split(param[1], ',');
	if (ft_testcoors(v))
		cam.viewp = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "Bad viewpoint data", des);
	ft_freesplit(v);
	v = ft_split(param[2], ',');
	if (ft_testvector(v))
		cam.normal = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "Invalid orient vector", des);
	ft_freesplit(v);
	if (ft_testfov(param[3]))
		cam.fov = ft_atoi(param[3]);
	else
		ft_free_cam(NULL, param, "Invalid FOV", des);
	ft_freesplit(param);
	cam.aspect_ratio = (double)16 / 9;
	*count += 1;
	return (cam);
}

t_light	init_light(char *line, int *count, char **des)
{
	t_light	light;
	char	**param;
	char	**lp;

	param = ft_split(line, ' ');
	lp = ft_split(param[1], ',');
	if (ft_testcoors(lp))
		light.lp = create_vec3(ft_atof(lp[0]), ft_atof(lp[1]),
				ft_atoi(lp[2]));
	else
		ft_free_light(lp, param, "Bad viewpoint data", des);
	ft_freesplit(lp);
	if (ft_testratio(param[2]))
		light.bright_ratio = ft_atof(param[2]);
	else
		ft_free_light(NULL, param, "Bad bright ratio", des);
	ft_freesplit(param);
	*count += 1;
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

bool	ft_init_env(char **desc, t_scene *scene)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (desc[i] != NULL)
	{
		if (ft_check_env(desc[i]) == 1)
			scene->amb = init_ambient(desc[i], &count, desc);
		else if (ft_check_env(desc[i]) == 2)
			scene->cam = init_camera(desc[i], &count, desc);
		else if (ft_check_env(desc[i]) == 3)
			scene->light = init_light(desc[i], &count, desc);
		i++;
	}
	if (count != 3)
		return (ft_error("Duplicate or missing A, C, L values"), false);
	return (true);
}
