/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:41:38 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 16:02:50 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_size_malloc(t_game *game, char **map)
{
	int	index;

	index = 0;
	while (map[index])
	{
		if (map[index + 1] == NULL)
		{
			if ((int)ft_strlen(map[index]) > game->map->width)
				game->map->width = (int)ft_strlen(map[index]);
		}
		else
		{
			if ((int)(ft_strlen(map[index]) - 1) > game->map->width)
				game->map->width = (int)ft_strlen(map[index]);
		}
		++index;
		++game->map->height;
	}
	game->map->size = game->map->height * game->map->width;
}

int	get_int_map(t_game *game, char **map)
{
	int	*tiles;
	int	index;
	int	rows;
	int	cols;
	
	rows = -1;
	index = 0;
	get_size_malloc(game, map);
	tiles = ft_calloc(game->map->size + 1, sizeof(int *));
	if (tiles == NULL)
		return (error_msg(game, MALLOC_ERROR));
	while (map[++rows])
	{
		cols = 0;
		while (map[rows][cols] != '\0' && map[rows][cols] != '\n')
		{
			if (ft_isalpha(map[rows][cols]))
			{
				game->map->player_x = cols;
				game->map->player_y = rows;
				tiles[index++] = 0;
			}
			else if (map[rows][cols] == ' ')
				tiles[index++] = 0;
			else
				tiles[index++] = map[rows][cols] - '0';
			++cols;
		}
		while (cols < game->map->width)
		{
			tiles[index++] = 0;
			++cols;
		}
	}
    game->map->tiles = tiles;
	return (0);
}
