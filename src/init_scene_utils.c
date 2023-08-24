/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:33:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/24 16:30:00 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	ft_free_amb(char **data, char **param, char *error_msg, char **des)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_freesplit(des);
	ft_error(error_msg);
	exit(1);
}

void	ft_free_cam(char **data, char **param, char *error_msg, char **des)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_freesplit(des);
	ft_error(error_msg);
	exit(1);
}

void	ft_free_light(char **data, char **param, char *error_msg, char **des)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_freesplit(des);
	ft_error(error_msg);
	exit(1);
}

bool	ft_testratio(char *param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if ((param[i] < '0' || param[i] > '9') && param[i] != '.' )
			return (false);
		i++;
	}
	if (ft_atof(param) < 0 || ft_atof(param) > 1)
		return (false);
	return (true);
}

bool	ft_testfov(char *param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if ((param[i] < '0' || param[i] > '9') && param[i] != '.' )
			return (false);
		i++;
	}
	if (ft_atof(param) < 0 || ft_atof(param) > 180)
		return (false);
	return (true);
}
