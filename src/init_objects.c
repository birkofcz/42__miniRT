/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:04:48 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/06 15:48:44 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_sp	ft_init_sphere(char *line)
{
	t_sp	sphere;
	char	**param;
	char	**coor;
	char	**rgb;

	param = ft_split(line, ' ');
	coor = ft_split(param[1], ',');
	sphere.center.x = ft_atof(coor[0]);
	sphere.center.y = ft_atof(coor[1]);
	sphere.center.z = ft_atof(coor[2]);
	ft_freesplit(coor);
	sphere.diameter = ft_atof(param[2]);
	rgb = ft_split(param[3], ',');
	sphere.color.r = ft_atoi(rgb[0]);
	sphere.color.g = ft_atoi(rgb[1]);
	sphere.color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (sphere);
}

t_pl	ft_init_plane(char *line)
{
	t_pl	plane;
	char	**param;
	char	**temp;
	char	**rgb;

	param = ft_split(line, ' ');
	temp = ft_split(param[1], ',');
	plane.point.x = ft_atof(temp[0]);
	plane.point.y = ft_atof(temp[1]);
	plane.point.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	temp = ft_split(param[2], ',');
	plane.normal.x = ft_atof(temp[0]);
	plane.normal.y = ft_atof(temp[1]);
	plane.normal.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	rgb = ft_split(param[3], ',');
	plane.color.r = ft_atoi(rgb[0]);
	plane.color.g = ft_atoi(rgb[1]);
	plane.color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (plane);
}

t_cy	ft_init_cylinder(char *line)
{
	t_cy	cylinder;
	char	**param;
	char	**temp;
	char	**rgb;

	param = ft_split(line, ' ');
	temp = ft_split(param[1], ',');
	cylinder.center.x = ft_atof(temp[0]);
	cylinder.center.y = ft_atof(temp[1]);
	cylinder.center.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	temp = ft_split(param[2], ',');
	cylinder.normal.x = ft_atof(temp[0]);
	cylinder.normal.y = ft_atof(temp[1]);
	cylinder.normal.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	cylinder.diameter = ft_atof(param[3]);
	cylinder.height = ft_atof(param[4]);
	rgb = ft_split(param[5], ',');
	cylinder.color.r = ft_atoi(rgb[0]);
	cylinder.color.g = ft_atoi(rgb[1]);
	cylinder.color.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (cylinder);
}

void	ft_init_objects(char **description, t_scene *scene, char *ident)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (description[i])
	{
		if (ft_isstr(description[i], ident))
		{
			if (ft_strncmp("sp", ident, ft_strlen(ident)) == 0)
				scene->sp[j] = ft_init_sphere(description[i]);
			if (ft_strncmp("pl", ident, ft_strlen(ident)) == 0)
				scene->pl[j] = ft_init_plane(description[i]);
			if (ft_strncmp("cy", ident, ft_strlen(ident)) == 0)
				scene->cy[j] = ft_init_cylinder(description[i]);
			j++;
		}
		i++;
	}
}
