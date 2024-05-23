/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:23 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:29:43 by vicalvez         ###   ########.fr       */
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

            draw_rect_to_img(game->cast_image, vector(xo, yo), vector(xo + maps, yo + maps), color);
            x++;
        }
        x = 0;
        y++;
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

    draw_line_to_img(game->main_image, vector(game->win_width / 2 - 7, game->win_height / 2), vector(game->win_width / 2 + 7, game->win_height / 2), 0xFFFFFF);
    draw_line_to_img(game->main_image, vector(game->win_width / 2, game->win_height / 2 - 7), vector(game->win_width / 2, game->win_height / 2 + 7), 0xFFFFFF);

    mlx_put_image_to_window(game->mlx, game->window, game->main_image, 0, 0);

    print_coords(game);
    show_tooltip(game);

    mlx_destroy_image(game->mlx, game->cast_image);
    return 0;
}