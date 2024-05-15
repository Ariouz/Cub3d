#include "../includes/cub3d.h"

int listen_key_press(int keycode, t_game *game)
{
    ft_printf("key: %d\n", keycode);

    if (keycode == KEY_ESCAPE)
        return listen_exit(game);
    
    // todo movement
    return (0);
}