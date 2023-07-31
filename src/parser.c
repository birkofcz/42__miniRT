/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:03:58 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/31 15:02:18 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/objects.h"
/* 
Testing the file - for "." and "rt"
 */
bool	ft_testfile(char *scene)
{
	char	**eval;

	if (ft_strchr(scene, "."))
	{
		eval = ft_split(scene, ".");
		if (eval[1])
		{
			if (ft_strncmp(eval[1], "rt", ft_strlen(eval[1])))
				return (ft_freesplit(eval), true);
		}
		return (ft_freesplit(eval), false);
	}
	return (false);
}

/* 
Taking argv[1] as arg, parsing based on identifier...
 */
int	ft_parser(char *scene)
{
	int	fd;
	char *line;

	if (ft_testfile(scene))
	{
		fd = open(scene ....);
		if (fd == -1)
			return (ft_error("Unable to open file"), 1);
		//line = get_next_line;
		//Identifier crossroads. (also need to init the structs with zeros somwhere. Maybe do another struct just to have information about the scene = flags 1/0 on objects...);
		
	}
	else
		return (ft_error("Invalid scene file"), 1);

}
