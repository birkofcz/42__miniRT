/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/31 16:00:47 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (ft_error("Missing scene file path"), 1);
	ft_parser(argv[1]);
	write(1, "test", 4);
	write(1, "\n", 1);
	return (0);
}
