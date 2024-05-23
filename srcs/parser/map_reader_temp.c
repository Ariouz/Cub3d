/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_temp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:09:17 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 14:25:44 by vicalvez         ###   ########.fr       */
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

static int count_line(t_game *game, char *file, size_t *line_count)
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

char	**get_temp_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char	**temp_map;
	size_t	line_count;

	line_count = 0;
	if (count_line(game, file, &line_count) != 0)
		return (NULL);
	temp_map = ft_calloc(line_count + 1, sizeof(char *));
	if (temp_map == NULL)
		return (NULL);
	fd = open(file, O_RDONLY, 0777);
	if (fd <= 2)
	{
		free(temp_map);
		return (NULL);
	}
	line = get_next_line(fd);
	line_count = 0;
	while (line != NULL)
	{
		temp_map[line_count++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	temp_map[line_count] = NULL;
	return (temp_map);
}

int	read_map_temp(t_game *game, char **argv)
{
	int		fd;
	char	**temp_map;

	if (check_file_extension(argv[0]) == 0)
		return (error_msg(game, WRONG_FILE_EXTENSION));
	temp_map = get_temp_map(game, argv[0]);
	if (temp_map == NULL)
		return (error_msg(game, MALLOC_ERROR));	
	if (get_asset(game, temp_map) != 0)
		return (1);
	return (0);
}