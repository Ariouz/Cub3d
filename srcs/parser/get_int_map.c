/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:41:38 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 19:38:45 by vicalvez         ###   ########.fr       */
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

void	set_player_coord(t_vector vec, t_game *game)
{
	game->map->player_x = vec.ix;
	game->map->player_y = vec.iy;
}

void	set_player_rotation(char c, t_game *game)
{
	if (c == 'N')
		game->spawn_angle = 270;
	else if (c == 'E')
		game->spawn_angle = 0;
	else if (c == 'S')
		game->spawn_angle = 90;
	else if (c == 'W')
		game->spawn_angle = 180;
}

int	*get_int_map2(t_game *game, char **map, int *tiles, t_save_line save)
{
	while (map[++save.rows])
	{
		save.cols = 0;
		while (map[save.rows][save.cols] != '\0'
			&& map[save.rows][save.cols] != '\n')
		{
			if (ft_isalpha(map[save.rows][save.cols]))
			{
				set_player_coord(vector(save.cols, save.rows), game);
				set_player_rotation(map[save.rows][save.cols], game);
				tiles[save.index++] = 0;
			}
			else if (map[save.rows][save.cols] == ' ')
				tiles[save.index++] = 0;
			else
				tiles[save.index++] = map[save.rows][save.cols] - '0';
			++save.cols;
		}
		while (save.cols < game->map->width)
		{
			tiles[save.index++] = 0;
			++save.cols;
		}
	}
	return (tiles);
}

int	get_int_map(t_game *game, char **map)
{
	int			*tiles;
	t_save_line	save;

	tiles = NULL;
	save.cols = 0;
	save.index = 0;
	save.rows = -1;
	get_size_malloc(game, map);
	tiles = ft_calloc(game->map->size + 1, sizeof(int *));
	if (tiles == NULL)
		return (error_msg(game, MALLOC_ERROR));
	game->map->tiles = get_int_map2(game, map, tiles, save);
	return (0);
}
