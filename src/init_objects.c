/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:04:48 by tkajanek          #+#    #+#             */
/*   Updated: 2023/08/26 15:00:46 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_sp	*ft_init_sphere(char *line)
{
	t_sp	*sphere;
	char	**param;
	char	**c;
	char	**rgb;

	sphere = (t_sp *)malloc(sizeof(t_sp)); 
	if (sphere == NULL)
		return (NULL);
	param = ft_split(line, ' ');
	if (ft_arraysize(param) != 4)
		return (ft_free_sp(NULL, param, sphere, "SP: Invalid params"), NULL);
	c = ft_split(param[1], ',');
	if (!ft_testcoors(c))
		return (ft_free_sp(c, param, sphere, "SP: Invalid coordinates"), NULL);
	sphere->center = create_vec3(ft_atof(c[0]), ft_atof(c[1]), ft_atof(c[2]));
	ft_freesplit(c);
	if (!ft_testparam(param[2]))
		return (ft_free_sp(NULL, param, sphere, "SP: Invalid dia"), NULL);
	sphere->diameter = ft_atof(param[2]);
	rgb = ft_split(param[3], ',');
	if (!ft_testcolor(rgb))
		return (ft_free_sp(rgb, param, sphere, "SP: Invalid color"), NULL);
	sphere->color = fill_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	return (ft_freesplit(rgb), ft_freesplit(param), sphere);
}

t_pl	*ft_init_plane(char *line)
{
	t_pl	*plane;
	char	**param;
	char	**t;
	char	**rgb;

	plane = (t_pl *)malloc(sizeof(t_pl)); 
	param = ft_split(line, ' ');
	if (ft_arraysize(param) != 4)
		return (ft_free_pl(NULL, param, plane, "PL: Invalid parameters"), NULL);
	t = ft_split(param[1], ',');
	if (!ft_testcoors(t))
		return (ft_free_pl(t, param, plane, "PL: Invalid point"), NULL);
	plane->point = create_vec3(ft_atof(t[0]), ft_atof(t[1]), ft_atof(t[2]));
	ft_freesplit(t);
	t = ft_split(param[2], ',');
	if (!ft_testvector(t))
		return (ft_free_pl(t, param, plane, "PL: Invalid normal vector"), NULL);
	plane->normal = create_vec3(ft_atof(t[0]), ft_atof(t[1]), ft_atof(t[2]));
	ft_freesplit(t);
	rgb = ft_split(param[3], ',');
	if (!ft_testcolor(rgb))
		return (ft_free_pl(rgb, param, plane, "PL: Invalid color"), NULL);
	plane->color = fill_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	return (ft_freesplit(rgb), ft_freesplit(param), plane);
}

t_cy	*ft_init_cylinder(char *line)
{
	t_cy	*cylinder;
	char	**param;
	char	**t;

	cylinder = (t_cy *)malloc(sizeof(t_cy));
	param = ft_split(line, ' ');
	if (ft_arraysize(param) != 6)
		return (ft_free_cy(NULL, param, cylinder, "CY: Invalid params"), NULL);
	t = ft_split(param[1], ',');
	if (!ft_testcoors(t))
		return (ft_free_cy(t, param, cylinder, "CY: Invalid center"), NULL);
	cylinder->center = create_vec3(ft_atof(t[0]), ft_atof(t[1]), ft_atof(t[2]));
	ft_freesplit(t);
	t = ft_split(param[2], ',');
	if (!ft_testvector(t))
		return (ft_free_cy(t, param, cylinder, "CY: Invalid norm vect"), NULL);
	cylinder->normal = create_vec3(ft_atof(t[0]), ft_atof(t[1]), ft_atof(t[2]));
	ft_freesplit(t);
	if (!ft_fillcyldiahei(cylinder, param[3], param[4]))
		return (ft_free_cy(NULL, param, cylinder, "CY: Bad dia/height"), NULL);
	t = ft_split(param[5], ',');
	if (!ft_testcolor(t))
		return (ft_free_cy(t, param, cylinder, "CY: Invalid color"), NULL);
	cylinder->color = fill_rgb(ft_atoi(t[0]), ft_atoi(t[1]), ft_atoi(t[2]));
	return (ft_freesplit(t), ft_freesplit(param), cylinder);
}

/* ORIGINAL FUNCTION BEFORE NORMINETTE BULLSHIT */
/* bool	ft_init_objects(char **description, t_scene *scene)
{
	int			i;
	t_object	*current;
	t_object	*new_object;

	i = 0;
	current = NULL;
	while (description[i])
	{
		if (ft_isstr(description[i], "sp") || ft_isstr(description[i], "pl")
			|| ft_isstr(description[i], "cy"))
		{
			new_object = (t_object *)malloc(sizeof(t_object));
			if (new_object == NULL)
				return (false);
			if (ft_strncmp(description[i], "sp", 2) == 0)
			{
				new_object->object = (void *)ft_init_sphere(description[i]);
				if (!(new_object->object))
					return (false);
				new_object->type = SPHERE;
			}
			else if (ft_strncmp(description[i], "pl", 2) == 0)
			{
				new_object->object = (void *) ft_init_plane(description[i]);
				if (!(new_object->object))
					return (false);
				new_object->type = PLANE;
			}
			else if (ft_strncmp(description[i], "cy", 2) == 0)
			{
				new_object->object = (void *) ft_init_cylinder(description[i]);
				if (!(new_object->object))
					return (false);
				new_object->type = CYLINDER;
			}
			new_object->next = NULL;
			if (current == NULL)
			{
				scene->head_object = new_object;
				current = new_object;
			}
			else
			{
				current->next = new_object;
				current = current->next;
			}
		}
		i++;
	}
	scene->object = scene->head_object;
	return (true);
} */

void	ft_freelist(t_scene *scene)
{
	t_object	*tmp;

	tmp = NULL;
	while (scene->head_object)
	{
		tmp = scene->head_object;
		scene->head_object = scene->head_object->next;
		free(tmp->object);
		free(tmp);
	}
}

bool	ft_init_objects(char **description, t_scene *scene)
{
	int			i;
	t_object	*current;
	t_object	*new_object;

	i = 0;
	current = NULL;
	new_object = NULL;
	while (description[i]) 
	{
		if (ft_isstr(description[i], "sp") || ft_isstr(description[i], "pl")
			|| ft_isstr(description[i], "cy")) 
		{
			new_object = init_new_object(description[i]);
			if (!new_object)
				return (ft_freelist(scene), false);
			append_to_scene(scene, &current, new_object);
		}
		i++;
	}
	scene->object = scene->head_object;
	return (true);
}
