/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:04:48 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/01 18:44:39 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
Counts the objects - sphere, plane or cylinder -
by the identifier in the description
 */
int	ft_count_objects(char **description, char *ident)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (description[i] != NULL)
	{
		if (ft_strncmp(description[i], ident, ft_strlen(ident)) == 0)
			count++;
		i++;
	}
	return (count);
}

int	ft_allocate_objects(t_scene *scene, char **description)
{
	int sphere_count;
	int	plane_count;
	int cylinder_count;

	sphere_count = ft_count_objects(description, "sp");
	plane_count = ft_count_objects(description, "pl");
	cylinder_count = ft_count_objects(description, "cy");

	if (sum(sphere_count, plane_count, cylinder_count) == 0)
		return (1);
	if (sphere_count != 0)
		scene->sp = (t_sp *)malloc(sizeof(t_sp) * sphere_count);
	else 
		scene->sp = NULL;
	if (plane_count != 0)
		scene->pl = (t_pl *)malloc(sizeof(t_pl) * plane_count);
	else
		scene->pl = NULL;
	if (cylinder_count != 0)
		scene->cy = (t_cy *)malloc(sizeof(t_cy) * cylinder_count);
	else
		scene->cy = NULL;
	return (0);
}

t_sp	*ft_init_sphere(char *line)
{
	t_sp	sphere;
	char	**param;
	char	**coor;
	char	**rgb;

	param = ft_split(line, ' ');
	coor = ft_split(param[1], ',');
	sphere.x = ft_atof(coor[0]);
	sphere.y = ft_atof(coor[1]);
	sphere.z = ft_atof(coor[2]);
	ft_freesplit(coor);
	sphere.diameter = ft_atof(param[2]);
	rgb = ft_split(param[3]);
	sphere.r = ft_atoi(rgb[0]);
	sphere.g = ft_atoi(rgb[1]);
	sphere.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (&sphere);
}

t_pl	*ft_init_plane(char *line)
{
	t_pl	plane;
	char	**param;
	char	**temp;
	char	**rgb;

	param = ft_split(line, ' ');
	temp = ft_split(param[1], ',');
	plane.x = ft_atof(temp[0]);
	plane.y = ft_atof(temp[1]);
	plane.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	temp = ft_split(param[2], ',');
	plane.vx = ft_atof(temp[0]);
	plane.vy = ft_atof(temp[1]);
	plane.vz = ft_atof(temp[2]);
	ft_freesplit(temp);
	rgb = ft_split(param[3]);
	plane.r = ft_atoi(rgb[0]);
	plane.g = ft_atoi(rgb[1]);
	plane.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (&plane);
}

t_cy	*ft_init_cylinder(char *line)
{
	t_cy	cylinder;
	char	**param;
	char	**temp;
	char	**rgb;

	param = ft_split(line, ' ');
	temp = ft_split(param[1], ',');
	cylinder.x = ft_atof(temp[0]);
	cylinder.y = ft_atof(temp[1]);
	cylinder.z = ft_atof(temp[2]);
	ft_freesplit(temp);
	temp = ft_split(param[2], ',');
	cylinder.vx = ft_atof(temp[0]);
	cylinder.vy = ft_atof(temp[1]);
	cylinder.vz = ft_atof(temp[2]);
	ft_freesplit(temp);
	cylinder.diameter = ft_atof(param[3]);
	cylinder.height = ft_atof(param[4]);
	rgb = ft_split(param[5]);
	cylinder.r = ft_atoi(rgb[0]);
	cylinder.g = ft_atoi(rgb[1]);
	cylinder.b = ft_atoi(rgb[2]);
	ft_freesplit(rgb);
	ft_freesplit(param);
	return (&plane);
}

void	ft_init_object(char **description, t_scene *scene, char *ident)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (description[i])
	{
		if (ft_strncmp(description[i], ident, ft_strlen(ident)) == 0)
		{
			if (ft_strncmp('sp', ident, ft_strlen(ident)) == 0)
				scene->sp[j] = ft_init_sp(description[i]);
			if (ft_strncmp('pl', ident, ft_strlen(ident)) == 0)
				scene->pl[j] = ft_init_sp(description[i]);
			if (ft_strncmp('cy', ident, ft_strlen(ident)) == 0)
				scene->cy[j] = ft_init_sp(description[i]);
			j++;
		}
		i++;
	}
}
