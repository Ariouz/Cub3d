#include "../includes/cub3d.h"

int init_player(t_game *game)
{
    t_player    *player;

    player = malloc(sizeof(t_player));
    if (!player)
        return (1);
    player->x = center_pos(game->map->player_x * TILE_SIZE);
    player->y = center_pos(game->map->player_y * TILE_SIZE);
    player->angle = 0;
    player->dirX = cos(player->angle) * PLAYER_SPEED;
    player->dirY = sin(player->angle) * PLAYER_SPEED;
    game->player = player;
    ft_printf("Player spawn: %d %d\n", (int) game->player->x, (int) game->player->y);
    return (0);
}

int init_game(t_game *game)
{
    game->mlx = NULL;
    game->window = NULL;
    game->map = NULL;
    game->mlx = mlx_init();
    game->win_width = 960;
    game->win_height = 540;
    game->cast_image = NULL;
    game->main_image = NULL;

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
    mlx_loop_hook(game->mlx, render_map, game);
    return (0);
}