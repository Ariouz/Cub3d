/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:17:59 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 13:29:23 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_first_last_rows(char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == '\n' && line[index + 1] == '\0')
			;
		else if (line[index] != ' ' && line[index] != '1')
			return (1);
		++index;
	}
	return (0);
}

static int	check_first_last_cols(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] && line[index] == ' ')
		++index;
	if (line[index] != '1')
		return (1);
	while (line[index] != '\0' && line[index] != '\n')
		++index;
	--index;
	if (line[index] != '1')
		return (1);
	return (0);
}

static int	check_surrounding(char **map, size_t rows, size_t cols)
{
	if ((map[rows + 1][cols] != '1' && map[rows + 1][cols] != ' ')
		|| (map[rows - 1][cols] != '1' && map[rows - 1][cols] != ' ')
		|| (map[rows][cols - 1] != '1' && map[rows][cols - 1] != ' ')
		|| (map[rows][cols + 1] != '1' && map[rows][cols + 1] != ' '))
		return (1);
	return (0);
}

static int	check_space_wall(char **map, size_t rows)
{
	size_t	cols;

	cols = 0;
	while (map[rows][cols] && map[rows][cols] == ' ')
		++cols;
	while (map[rows][cols] != '\0' && map[rows][cols] != '\n')
	{
		if (map[rows][cols] == ' ')
		{
			if (check_surrounding(map, rows, cols) != 0)
				return (1);
		}
		++cols;
	}
	return (0);
}

int	check_wall(char **map)
{
	size_t	rows;

	rows = 0;
	while (map[rows])
	{
		if (rows == 0 || map[rows + 1] == NULL)
		{
			if (check_first_last_rows(map[rows]) != 0)
				return (1);
		}
		else if (check_first_last_cols(map[rows]) != 0 || check_space_wall(map, rows) != 0)
			return (1);
		++rows;
	}
	return (0);
}
