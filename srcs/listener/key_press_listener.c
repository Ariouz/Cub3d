#include "cub3d.h"

int listen_key_press(int keycode, t_game *game)
{
    t_pressed_keys *keys;

    keys = game->keys;
    //printf("keycode %d\n", keycode);
    if (keycode == KEY_ESCAPE)
        return listen_exit(game);

    if (keycode == KEY_W)
        keys->w = 1;
    if (keycode == KEY_A)
        keys->a = 1;
    if (keycode == KEY_S)
        keys->s = 1;
    if (keycode == KEY_D)
        keys->d = 1;
    if (keycode == KEY_ARROW_LEFT)
        keys->la = 1;
    if (keycode == KEY_ARROW_RIGHT)
        keys->ra = 1;
    if (keycode == KEY_SPACE)
    {
        game->mouse_lock = -game->mouse_lock;
        if (game->mouse_lock)
            mlx_mouse_hide(game->mlx, game->window);
        else
            mlx_mouse_show(game->mlx, game->window);
    }

    return (0);
}

int listen_key_release(int keycode, t_game *game)
{
    t_pressed_keys *keys;

    keys = game->keys;
    if (keycode == KEY_ESCAPE)
        return listen_exit(game);

    if (keycode == KEY_W)
        keys->w = 0;
    if (keycode == KEY_A)
        keys->a = 0;
    if (keycode == KEY_S)
        keys->s = 0;
    if (keycode == KEY_D)
        keys->d = 0;
    if (keycode == KEY_ARROW_LEFT)
        keys->la = 0;
    if (keycode == KEY_ARROW_RIGHT)
        keys->ra = 0;
    return (0);
}

/*
t_player    *player;

    player = game->player;
    
    
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
    */