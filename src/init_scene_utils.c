/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:33:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/22 16:36:00 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	ft_free_amb(char **data, char **param, bool *error, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_error(error_msg);
	*error = true;
}

void	ft_free_cam(char **data, char **param, bool *error, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_error(error_msg);
	*error = true;
}

void	ft_free_light(char **data, char **param, bool *error, char *error_msg)
{
	if (data)
		ft_freesplit(data);
	ft_freesplit(param);
	ft_error(error_msg);
	*error = true;
}
