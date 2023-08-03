/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:04:22 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:07:14 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Service function to use for writing an error message to stderr (with newline)
and returning defined int - could be used in return statements as is
 */

int	ft_puterror(char *message, int return_num)
{
	int		len;

	len = ft_strlen(message);
	write(2, message, len);
	write(2, "\n", 1);
	return (return_num);
}
