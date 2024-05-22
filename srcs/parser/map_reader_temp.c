/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_temp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:09:17 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/22 16:09:33 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_file_extension(char *file)
{
	size_t	index;

	index = 0;
	if (ft_strlen(file) < 5)
		return (0);
	while (file[index])
		++index;
	index = index - 4;
	if (ft_strncmp(file + index, ".cub", 5) != 0)
		return (0);
	return (1);
}

static int count_line(t_game *game, char *file, int *line_count)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY, 0777);
	if (fd <= 2)
		return (error_open(game, file));
	line = get_next_line(fd);
	while (line != NULL)
	{
		*(++line_count);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}	

int	get_temp_map(t_game *game, char **temp_map, char *file)
{
	int		fd;
	size_t line_count;

	line_count = 0;
	if (count_line(game, file, &line_count) != 0)
		return (1);
	temp_map = ft_calloc(line_count + 1, sizeof(char *));
	if (temp_map == NULL)
		return (error_msg(game, MALLOC_ERROR));
	
}

/*static int	get_asset(t_game *game, int fd)
{
	char	*line;


}*/

int	read_map_temp(t_game *game, char **argv)
{
	int		fd;
	char	**temp_map;

	if (check_file_extension(argv[0]) == 0)
		return (error_msg(game, WRONG_FILE_EXTENSION));
	if (get_temp_map(game, temp_map, argv[0]))
		return (1);
	if (get_asset(game, fd) != 0)
		return (1);
	return (0);
}