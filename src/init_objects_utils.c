/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:30:50 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/26 10:53:21 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/*
Counts the objects - sphere, plane or cylinder -
by the identifier in the description
 */
int	ft_count_objects(char **description)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (description[i] != NULL)
	{
		if (ft_isstr(description[i], "sp") || ft_isstr(description[i], "pl")
			|| ft_isstr(description[i], "cy"))
			count++;
		i++;
	}
	return (count);
}

bool	ft_fillcyldiahei(t_cy *cyl, char *dia, char *hei)
{
	if ((!ft_testparam(dia)) || (!ft_testparam(hei)))
		return (false);
	cyl->diameter = ft_atof(dia);
	cyl->height = ft_atof(hei);
	return (true);
}

void	ft_free_sp(char **data, char **param, t_sp *sphere, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	free(sphere);
	ft_error(error_msg);
}

void	ft_free_pl(char **data, char **param, t_pl *plane, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	free(plane);
	ft_error(error_msg);
}

void	ft_free_cy(char **data, char **param, t_cy *cyl, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	if (cyl)
		free(cyl);
	ft_error(error_msg);
}
