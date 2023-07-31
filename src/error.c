/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:08:42 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/31 14:11:15 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"

/* 
To put error messages to screen, taking the message as arg
 */
void	ft_error(char *message)
{
	int		len;

	len = ft_strlen(message);
	write(2, "Error: ", 8);
	write(2, message, len);
	write(2, "\n", 1);
}