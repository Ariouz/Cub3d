/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:23 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/22 17:18:32 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    draw_map(t_game *game, t_map *map)
{
    int x;
    int y;
    int xo;
    int yo;
    int color;
    int maps;
    
    x = 0;
    y = 0;
    maps = TILE_SIZE;
    while (y < map->height)
    {
        while (x < map->width)
        {
            if (get_tile_at(x, y, map) == MAP_WALL)
                color = 0x111111;
            else
                color = 0x777777;
            xo = x * maps;
            yo = y * maps;

            draw_rect_to_img(game->cast_image, xo, yo, xo + maps, yo + maps, color, 0);
            x++;
        }
        x = 0;
        y++;
    }
}

void    move(t_game *game, t_player *player, t_pressed_keys *keys)
{
    t_map *map;
    int xo;
    int yo;
    int ipx;
    int ipx_add_xo;
    int ipx_sub_xo;
    int ipy;
    int ipy_add_yo;
    int ipy_sub_yo;

    map = game->map;
    if (player->dirX < 0)
        xo = -20;
    else
        xo = 20;
    if (player->dirY < 0)
        yo = -20;
    else
        yo = 20;
    ipx = player->x / TILE_SIZE;
    ipx_add_xo = (player->x + xo) / TILE_SIZE;
    ipx_sub_xo = (player->x - xo) / TILE_SIZE;

    ipy = player->y / TILE_SIZE;
    ipy_add_yo = (player->y + yo) / TILE_SIZE;
    ipy_sub_yo = (player->y - yo) / TILE_SIZE;


    if (keys->w)
    {
        if (map->tiles[ipy*map->width + ipx_add_xo] == 0)
            player->x += player->dirX;
        if (map->tiles[ipy_add_yo * map->width + ipx] == 0)
            player->y += player->dirY;
    }

    if (keys->s)
    {
        if (map->tiles[ipy*map->width + ipx_sub_xo] == 0)
            player->x -= player->dirX;
        if (map->tiles[ipy_sub_yo * map->width + ipx] == 0)
            player->y -= player->dirY;
    }
    
    if (keys->a)
    {
        player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y / TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;

        player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y / TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
    }

    if (keys->d)
    {
        player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y/ TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;

        player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y / TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;

    }

    if (keys->la)
    {
        player->angle -= PLAYER_ROTATION_SPEED;
        if (player->angle < 0)
            player->angle += 2 * PI;
        player->dirX = cos(player->angle) * PLAYER_SPEED;
        player->dirY = sin(player->angle) * PLAYER_SPEED;
    }

    if (keys->ra)
    {
        player->angle += PLAYER_ROTATION_SPEED;
        if (player->angle > 2 * PI)
            player->angle -= 2 * PI;
        player->dirX = cos(player->angle) * PLAYER_SPEED;
        player->dirY = sin(player->angle) * PLAYER_SPEED;
    }
}

int    render_map(t_game *game)
{
    //int *tiles = game->map->tiles;
    t_player    *player;

    player = game->player;

    game->cast_image = mlx_new_image(game->mlx, game->win_width, game->win_height);
    
    move(game, game->player, game->keys);

    //draw_map(game, game->map);
    draw_rays(game);


    put_img_to_img(game->main_image, game->cast_image, 0, 0);
    draw_minimap(game, game->map, player);

    draw_line_to_img(game->main_image, game->win_width / 2 - 7, game->win_height / 2, game->win_width / 2 + 7, game->win_height / 2, 0xFFFFFF);
    draw_line_to_img(game->main_image, game->win_width / 2, game->win_height / 2 - 7, game->win_width / 2, game->win_height / 2 + 7, 0xFFFFFF);

    mlx_put_image_to_window(game->mlx, game->window, game->main_image, 0, 0);

    print_coords(game);

    mlx_destroy_image(game->mlx, game->cast_image);
    return 0;
}