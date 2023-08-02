/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:03:58 by sbenes            #+#    #+#             */
/*   Updated: 2023/08/02 15:16:39 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"
/* 
Testing the file - for "." and "rt"
 */
bool	ft_testfile(char *scene)
{
	int	len;

	len = ft_strlen(scene);
	if (len < 3)
		return (false);
	if (!ft_strncmp(scene + len - 3, ".rt", 3))
		return (true);
	return (false);
}

/* 
Taking argv[1] as arg, parsing based on identifier...
 */
int	ft_parser(char *scene)
{
	int		fd;
	char	*line;
	char	*file;
	char	**description;

	line = ft_strdup("");
	file = NULL;
	fd = open(scene, O_RDONLY);
	if (fd == -1)
		return (ft_error("Unable to open file"), 1);
	if (ft_testfile(scene))
	{
		while (line != NULL)
		{
			file = ft_strjoin_gnl(file, line);
			free(line);
			line = get_next_line (fd);
		}
	}
	else
		return (ft_error("Invalid scene file"), 1);
	description = ft_split(file, '\n');
	ft_init(description);
	return (0);
	//Identifier crossroads. (also need to init the structs with zeros somwhere. Maybe do another struct just to have information about the scene = flags 1/0 on objects...);
}
