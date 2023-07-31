/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:12 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/31 14:38:23 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/* pouzito ze so_long. Neupraveno 

void	parse_map(char *map_file, t_map_data *map)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		ft_error(0, NULL, NULL);
	init_map_data(map, fd);
	while (map->line != NULL)
	{
		map->extracted_map = ft_strjoin_gnl(map->extracted_map, map->line);
		free(map->line);
		map->line = get_next_line (fd);
		map->h++;
	}
	map->matrix = ft_split(map->extracted_map, '\n');
	free(map->extracted_map);
	free(map->line);
	if (map->matrix[0])
		map->w = ft_strlen(map->matrix[0]);
	check_symbols(map->matrix, map);
	check_rectangularity(map->matrix);
	check_prison(map->matrix, map->h, map->w);
	check_valid_path(map->matrix, map);
	close(fd);
}
*/

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_error("Missing scene file path"), 1);
	ft_parser(argv[1]);
	write(1, "test", 4);
	write(1, "\n", 1);
	return (0);
}