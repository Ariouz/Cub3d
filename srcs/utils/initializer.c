/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:39 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/22 17:49:49 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_player(t_game *game)
{
    t_player    *player;

    player = malloc(sizeof(t_player));
    if (!player)
        return (1);
    player->x = center_pos(game->map->player_x * TILE_SIZE);
    player->y = center_pos(game->map->player_y * TILE_SIZE);
    player->angle = to_radians(0);
    player->dirX = cos(player->angle) * PLAYER_SPEED;
    player->dirY = sin(player->angle) * PLAYER_SPEED;
    player->mouseX = 0;
    game->player = player;
    return (0);
}

void    init_keys(t_game *game)
{
    t_pressed_keys *keys;

    keys = malloc(sizeof(t_pressed_keys));
    keys->w = 0;
    keys->a = 0;
    keys->s = 0;
    keys->d = 0;
    keys->la = 0;
    keys->ra = 0;
    game->keys = keys;
}

void    init_assets(t_game *game)
{
    t_assets *assets;
    int w;
    int h;

    w = 0;
    h = 0;
    assets = malloc(sizeof(t_assets));
    assets->north_wall = mlx_xpm_file_to_image(game->mlx, "assets/north_wall.xpm", &w, &h);
    assets->south_wall = mlx_xpm_file_to_image(game->mlx, "assets/south_wall.xpm", &w, &h);
    assets->east_wall = mlx_xpm_file_to_image(game->mlx, "assets/east_wall.xpm", &w, &h);
    assets->west_wall = mlx_xpm_file_to_image(game->mlx, "assets/west_wall.xpm", &w, &h);
    assets->floor_color = 0x444444;
    assets->ceil_color = 0x777777;
    game->assets = assets;
}

int init_game(t_game *game)
{
    game->mlx = NULL;
    game->window = NULL;
    game->map = NULL;
    game->mlx = mlx_init();
    game->win_width = 848;
    game->win_height = 480;
    game->cast_image = NULL;
    game->main_image = NULL;
    init_keys(game);
    init_assets(game);

    if (game->mlx == NULL)
    {
        free(game);
        return (1);
    }
    game->window = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3d");
    init_listener(game);
    if (init_map(game) != 0)
    {
        clean(game);
        return (1);
    }
    init_player(game);
    game->main_image = mlx_new_image(game->mlx, game->win_width, game->win_height);
    game->cast_image = mlx_new_image(game->mlx, game->win_width, game->win_height);
    mlx_mouse_move(game->mlx, game->window, game->win_height / 2, game->win_height / 2);
    mlx_mouse_hide(game->mlx, game->window);
    mlx_loop_hook(game->mlx, render_map, game);
    return (0);
}