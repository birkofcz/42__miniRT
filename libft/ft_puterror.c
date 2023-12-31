/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:17:00 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:18:32 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Puts error message sent as arg to stderr. 
If there is a need for return value, use ft_puterror_rv;
 */
void	ft_puterror(char *message)
{
	int		len;

	len = ft_strlen(message);
	write(2, message, len);
	write(2, "\n", 1);
}
