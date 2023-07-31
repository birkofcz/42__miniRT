/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:08:42 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/31 15:38:22 by tkajanek         ###   ########.fr       */
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