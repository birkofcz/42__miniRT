/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:46:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/03 15:12:20 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
ft_strncmp, but convinient and more usable with logical True of False.
strncmp returns 0 when strings matching, which is logically counter-intuitive
 */
bool	ft_isstr(char *input, char *to_compare)
{
	if (!ft_strncmp(input, to_compare, ft_strlen(to_compare)))
		return (true);
	return (false);
}
