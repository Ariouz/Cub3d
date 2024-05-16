#include "cub3d.h"

int listen_key_press(int keycode, t_game *game)
{
    t_player    *player;

    player = game->player;
    if (keycode == KEY_ESCAPE)
        return listen_exit(game);
    
    if (keycode == KEY_W)
    {
        player->x += player->dirX;
        player->y += player->dirY;
    }

    if (keycode == KEY_S)
    {
        player->x -= player->dirX;
        player->y -= player->dirY;
    }

    if (keycode == KEY_A)
    {
        player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;
        player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;
    }

    if (keycode == KEY_D)
    {
        player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;
        player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
    }

    if (keycode == KEY_ARROW_LEFT)
    {
        player->angle -= PLAYER_ROTATION_SPEED;
        if (player->angle < 0)
            player->angle += 2 * PI;
        player->dirX = cos(player->angle) * PLAYER_SPEED;
        player->dirY = sin(player->angle) * PLAYER_SPEED;
    }

    if (keycode == KEY_ARROW_RIGHT)
    {
        player->angle += PLAYER_ROTATION_SPEED;
        if (player->angle > 2 * PI)
            player->angle -= 2 * PI;
        player->dirX = cos(player->angle) * PLAYER_SPEED;
        player->dirY = sin(player->angle) * PLAYER_SPEED;
    }

    return (0);
}