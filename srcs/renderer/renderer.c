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

            draw_rect_to_img(game->cast_image, xo, yo, xo + maps, yo + maps, color);
            x++;
        }
        x = 0;
        y++;
    }
}

int    render_map(t_game *game)
{
    int *tiles = game->map->tiles;
    t_player    *player;

    player = game->player;
    (void) player;
    (void) tiles;

    game->cast_image = mlx_new_image(game->mlx, game->win_width, game->win_height);
    
    //draw_map(game, game->map);

    draw_rays(game);
    draw_rect_to_img(game->cast_image, player->x - 10, player->y - 10, player-> x + 10, player->y + 10, 0xffff00);
    draw_line_to_img(game->cast_image, player->x, player->y, player->x + player->dirX * 5, player->y + player->dirY * 5, 0xFFFFFF);


    put_img_to_img(game->main_image, game->cast_image, 0, 0);
    mlx_put_image_to_window(game->mlx, game->window, game->main_image, 0, 0);
    mlx_destroy_image(game->mlx, game->cast_image);
    return 0;
}