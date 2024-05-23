/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:29:23 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 16:59:37 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_struct_map(t_map *map)
{
	if (map->tiles != NULL)
		free(map->tiles);
	map->tiles = NULL;
	free(map);
}

void	clean(t_game *game)
{
	if (game->keys != NULL)
		free(game->keys);
	game->keys = NULL;
	if (game->map != NULL)
		free_struct_map(game->map);
	game->map = NULL;
	if (game->player != NULL)
		free(game->player);
	game->player = NULL;
	if (game->assets != NULL)
	{
		if (game->assets->east_wall != NULL)
			mlx_destroy_image(game->mlx, game->assets->east_wall);
		game->assets->east_wall = NULL;
		if (game->assets->north_wall != NULL)
			mlx_destroy_image(game->mlx, game->assets->north_wall);
		game->assets->north_wall = NULL;
		if (game->assets->south_wall != NULL)
			mlx_destroy_image(game->mlx, game->assets->south_wall);
		game->assets->north_wall = NULL;
		if (game->assets->west_wall != NULL)
			mlx_destroy_image(game->mlx, game->assets->west_wall);
		game->assets->west_wall = NULL;
		free(game->assets);
	}
	game->assets = NULL;
	if (game->main_image != NULL)
		mlx_destroy_image(game->mlx, game->main_image);
	game->main_image = NULL;
	if (game->cast_image != NULL)
		mlx_destroy_image(game->mlx, game->cast_image);
	game->cast_image = NULL;
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	game->mlx = NULL;
}
