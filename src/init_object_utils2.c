/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:39:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/25 16:42:05 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

bool	ft_testparam(char *param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if ((param[i] < '0' || param[i] > '9') && param[i] != '.' )
			return (false);
		i++;
	}
	return (true);
}

bool	ft_testcoors(char **coors)
{
	int	i;
	int	y;

	i = 0;
	if (ft_arraysize(coors) != 3)
		return (false);
	while (coors[i])
	{
		y = 0;
		while (coors[i][y])
		{
			if ((coors[i][y] < '0' || coors[i][y] > '9') && 
				(coors[i][y] != '.' && coors[i][y] != '-'))
				return (false);
			y++;
		}
		i++;
	}
	return (true);
}

bool	ft_testvector(char **vector)
{
	int		i;
	int		y;
	double	magnitude;

	i = 0;
	if (ft_arraysize(vector) != 3)
		return (false);
	while (vector[i])
	{
		y = 0;
		while (vector[i][y])
		{
			if ((vector[i][y] < '0' || vector[i][y] > '9') && 
				(vector[i][y] != '.' && vector[i][y] != '-'))
				return (false);
			y++;
		}
		i++;
	}
	magnitude = pow(ft_atof(vector[0]), 2) + pow(ft_atof(vector[1]), 2) 
		+ pow(ft_atof(vector[2]), 2);
	if (fabs(magnitude - 1) > 0.1)
		return (false);
	return (true);
}

bool	ft_testcolor(char **color)
{
	int	i;
	int	y;
	int	color_value;

	i = 0;
	if (ft_arraysize(color) != 3)
		return (false);
	while (color[i]) 
	{
		y = 0;
		while (color[i][y])
		{
			if (color[i][y] < '0' || color[i][y] > '9') 
				return (false);
			y++;
		}
		color_value = ft_atoi(color[i]);
		if (color_value < 0 || color_value > 255)
			return (false);
		i++;
	}
	return (true);
}
