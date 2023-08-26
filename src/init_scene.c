/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:11:15 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/26 14:02:09 by sbenes           ###   ########.fr       */
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
	if (ft_arraysize(param) != 3)
		ft_free_amb(NULL, param, "AMB: Invalid parameters", des);
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

t_cam	init_camera_2(t_cam cam, char **param, char **des)
{
	char	**v;

	v = ft_split(param[1], ',');
	if (ft_testcoors(v))
		cam.viewp = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "CAM: Bad viewpoint data", des);
	ft_freesplit(v);
	v = ft_split(param[2], ',');
	if (ft_testvector(v))
		cam.normal = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "CAM: Invalid orient vector", des);
	ft_freesplit(v);
	if (ft_testfov(param[3]))
		cam.fov = ft_atoi(param[3]);
	else
		ft_free_cam(NULL, param, "CAM: Invalid FOV", des);
	ft_freesplit(param);
	return (cam);
}

t_cam	init_camera(char *line, int *count, char **des)
{
	t_cam	cam;
	char	**param;
	char	**v;

	ft_memset(&cam, 0, sizeof(t_cam));
	param = ft_split(line, ' ');
	if (ft_arraysize(param) != 4)
		ft_free_cam(NULL, param, "CAM: Invalid parameters", des);
	v = ft_split(param[1], ',');
	if (ft_testcoors(v))
		cam.viewp = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "CAM: Bad viewpoint data", des);
	ft_freesplit(v);
	cam = init_camera_2(cam, param, des);
	cam.aspect_ratio = (double) WIDTH / HEIGHT;
	*count += 1;
	return (cam);
}

/* Complete init camera before damn norminette split... */
/* t_cam	init_camera(char *line, int *count, char **des)
{
	t_cam	cam;
	char	**param;
	char	**v;

	param = ft_split(line, ' ');
	if (ft_arraysize(param) != 4)
		ft_free_cam(NULL, param, "CAM: Invalid parameters", des);
	v = ft_split(param[1], ',');
	if (ft_testcoors(v))
		cam.viewp = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "CAM: Bad viewpoint data", des);
	ft_freesplit(v);
	v = ft_split(param[2], ',');
	if (ft_testvector(v))
		cam.normal = create_vec3(ft_atof(v[0]), ft_atof(v[1]), ft_atof(v[2]));
	else
		ft_free_cam(v, param, "CAM: Invalid orient vector", des);
	ft_freesplit(v);
	if (ft_testfov(param[3]))
		cam.fov = ft_atoi(param[3]);
	else
		ft_free_cam(NULL, param, "CAM: Invalid FOV", des);
	ft_freesplit(param);
	cam.aspect_ratio = (double) WIDTH / HEIGHT;
	*count += 1;
	return (cam);
} */

t_light	init_light(char *line, int *count, char **des)
{
	t_light	light;
	char	**param;
	char	**lp;

	param = ft_split(line, ' ');
	if (ft_arraysize(param) != 4)
		ft_free_light(NULL, param, "LIGHT: Invalid parameters", des);
	lp = ft_split(param[1], ',');
	if (ft_testcoors(lp))
		light.lp = create_vec3(ft_atof(lp[0]), ft_atof(lp[1]),
				ft_atoi(lp[2]));
	else
		ft_free_light(lp, param, "LIGHT: Bad viewpoint data", des);
	ft_freesplit(lp);
	if (ft_testratio(param[2]))
		light.bright_ratio = ft_atof(param[2]);
	else
		ft_free_light(NULL, param, "LIGHT: Bad bright ratio", des);
	ft_freesplit(param);
	*count += 1;
	return (light);
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
