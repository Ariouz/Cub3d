/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:08 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 16:26:06 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_coords(t_game *game)
{
    char *x;
    char *y;
    char *coords;
    char *facing;
    int da;

    x = ft_strjoin("x: ", ft_itoa(game->player->x));
    y = ft_strjoin(x, " y: ");
    free(x);
    coords = ft_strjoin(y, ft_itoa(game->player->y));
    free(y);
    mlx_string_put(game->mlx, game->window, game->win_width - MINIMAP_SIDE_LEN - 10, MINIMAP_SIDE_LEN + 25, 0xFFFFFF, coords);
    free(coords);

    da = to_degrees(game->player->angle);
    if (da >= 315 || (da >= 0 && da <= 45))
        facing = ft_strdup("Facing: East");
    else if (da > 45 && da <= 135)
        facing = ft_strdup("Facing: South");
    else if (da > 135 && da <= 225)
        facing = ft_strdup("Facing: West");
    else
        facing = ft_strdup("Facing: North");
    
    if (facing)
    {
        mlx_string_put(game->mlx, game->window, game->win_width - MINIMAP_SIDE_LEN - 10, MINIMAP_SIDE_LEN + 40, 0xFFFFFF, facing);
        free(facing);
    }
}

void    draw_minimap(t_game *game, t_map *map, t_player *player)
{
    (void) player;
    (void) map;
    int x;
    int y;
    int mpx;
    int mpy; 

    x = game->win_width - MINIMAP_SIDE_LEN - 20;
    y = 10;

    draw_rect_to_img(game->main_image, vector(x, y), vector(x + MINIMAP_SIDE_LEN, y + MINIMAP_SIDE_LEN), 0xFF8c00); // background
    
    mpx = x + MINIMAP_SIDE_LEN / 2;
    mpy = y + MINIMAP_SIDE_LEN / 2;

    int radius;
    int rx;
    int ry;

    int px;
    int py;

    px = player->x / TILE_SIZE;
    py = player->y / TILE_SIZE;

    int tx;
    int ty;

    int t_size;
    int t_color;
    t_size = 12;

    radius = 4;
    rx = -radius;
    while (rx < radius)
    {
        ry = -radius;
        tx = rx;
        while (ry < radius)
        {
            ty = ry;      
            if ((py + ry) < 0 || (py + ry) >= map->height || (px + rx) < 0 || (px + rx) >= map->width)
                t_color = 0x111111;      
            else if (map->tiles[(py + ry) * map->width + (px + rx)] == MAP_WALL)
                t_color = 0x222222;  
            else
                t_color = 0x999999;      
            draw_rect_to_img(game->main_image, vector(mpx + (tx * t_size), mpy + (ty * t_size)), vector(mpx + (tx * t_size) + t_size, mpy + (ty * t_size) + t_size), t_color);      
        
            ry++;
        }
        rx++;
    }
    draw_rect_to_img(game->main_image, vector(mpx - 2, mpy - 2), vector(mpx + 2, mpy + 2), 0xFFFFFF); // player
}
