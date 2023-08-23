/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:45:35 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/23 14:46:01 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_key_event(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		ft_endgame(scene);
	else
		return (1);
	return (0);
}
