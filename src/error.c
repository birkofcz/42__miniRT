/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:08:42 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:03:53 by sbenes           ###   ########.fr       */
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
	write(2, "Error: \n", 9);
	write(2, message, len);
	write(2, "\n", 1);
}
