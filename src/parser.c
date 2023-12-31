/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:03:58 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/26 13:46:05 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
/* 
Testing the file - for "." and "rt"
 */
bool	ft_testfile(char *input)
{
	int	len;

	len = ft_strlen(input);
	if (len < 3)
		return (false);
	if (!ft_strncmp(input + len - 3, ".rt", 3))
		return (true);
	return (false);
}

/* 
Taking argv[1] as arg, parsing based on identifier...
 */
int	ft_parser(char *file, t_scene *scene, int fd)
{
	char	*line;
	char	*input;
	char	**description;

	line = ft_strdup("");
	input = ft_strdup("");
	if (ft_testfile(file))
	{
		while (line != NULL)
		{
			input = ft_strjoin_gnl(input, line);
			free(line);
			line = get_next_line(fd);
		}
	}
	else
		return (free(input), free(line), ft_error("Invalid scene file"), 1);
	description = ft_split(input, '\n');
	free(input);
	if (ft_init(description, scene) == 1)
		return (1);
	return (0);
}
