#include "../includes/cub3d.h"

void    init_listener(t_game *game)
{
    mlx_hook(game->window, DESTROY_HOOK, 0, listen_exit, game);
    mlx_hook(game->window, KEY_PRESSED_HOOK, (1L<<0), listen_key_press, game);
    mlx_hook(game->window, KEY_RELEASE_HOOK, (1L<<1), listen_key_release, game);
}