/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:45:35 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 17:24:59 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_key_event(int key, t_mlxdata *mlxdata)
{
	//printf("%d\n", key);
	if (key == KEY_ESC)
		ft_clean_exit(mlxdata);
	// more functions follow if needed
/* 	else if (key == KEY_PLUS)
		ft_zoom(f, 0.5); */
	else
		return (1);
	//ft_render(mlxdata, scene); //re-render the image for window if neccessary when some key pressed;
	return (0);
}