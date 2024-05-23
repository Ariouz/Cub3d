/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_asset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:56:30 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 17:55:34 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*static void	print_test(t_game *game)
{
	printf("Debut du test\n");
	printf("floor color: %d\n", game->assets->floor_color);
	printf("ceiling color: %d\n", game->assets->ceil_color);
	printf("north ptr: %p\n", game->assets->north_wall);
	printf("west ptr: %p\n", game->assets->west_wall);
	printf("east ptr: %p\n", game->assets->east_wall);
	printf("south ptr: %p\n", game->assets->south_wall);
	printf("Fin du test\n");
	return ;
}*/

static int	check_asset(t_assets *assets)
{
	if (assets->ceil_color == -1 || assets->floor_color == -1)
		return (1);
	if (assets->east_wall == NULL)
		return (1);
	if (assets->north_wall == NULL)
		return (1);
	if (assets->south_wall == NULL)
		return (1);
	if (assets->west_wall == NULL)
		return (1);
	return (0);
}

static int	check_line(t_game *game, t_assets *assets, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (get_north_asset(game, assets, line));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (get_south_asset(game, assets, line));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (get_west_asset(game, assets, line));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (get_east_asset(game, assets, line));
	else if (ft_strncmp(line, "F", 1) == 0)
		return (get_floor_color(game, assets, line));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (get_ceiling_color(game, assets, line));
	else if (ft_strncmp(line, "\n", 1) == 0)
		return (0);
	else if (ft_strncmp(line, " ", 1) == 0 || ft_strncmp(line, "1", 1) == 0
		|| ft_strncmp(line, "0", 1) == 0)
		return (0);
	else
		return (error_msg(game, WRONG_MAP_ARGUMENT));
	return (0);
}

int	get_asset(t_game *game, char **temp_map)
{
	t_assets	*assets;
	size_t		index;

	index = 0;
	assets = ft_calloc(1, sizeof(t_assets));
	if (assets == NULL)
	{
		free_temp_map(temp_map);
		return (error_msg(game, MALLOC_ERROR));
	}
	game->assets = assets;
	assets->floor_color = -1;
	assets->ceil_color = -1;
	while (temp_map[index])
	{
		if (check_line(game, assets, temp_map[index++]) != 0)
		{
			free_assets(game);
			free_temp_map(temp_map);
			return (1);
		}
	}
	if (check_asset(game->assets) != 0)
		return (error_msg(game, MISSING_ASSETS));
	return (0);
}
