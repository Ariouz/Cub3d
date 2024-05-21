#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/gnl/get_next_line.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define PI 3.1415926535
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533

# define CARDINAL_NS 1
# define CARDINAL_WE 0

# define PLAYER_SPEED 8
# define PLAYER_ROTATION_SPEED 0.1
# define TILE_SIZE 64
# define PLAYER_FOV 60

# define DESTROY_HOOK 17
# define KEY_PRESSED_HOOK 2
# define KEY_RELEASE_HOOK 3

# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_LEFT 65361

# define MAP_WALL 1
# define MAP_AIR 0

typedef struct s_raycast
{
    int r;
    int mx;
    int my;
    int mp;
    int dof;
    int px;
    int py;
    double rx;
    double ry;
    double ra;
    double xo;
    double yo;
    double atan;

    double dis_h;
    double hx;
    double hy;
    double dis_v;
    double vx;
    double vy;
    double dist;
}   t_raycast;

typedef struct s_player
{
    double x;
    double y;
    double dirX;
    double dirY;
    double angle;
}   t_player;

typedef struct s_map_setting
{
    int height;
    int width;
    int size;
}   t_map_setting;

typedef struct s_map
{
    int *tiles;
    int height;
    int width;
    int player_x;
    int player_y;
    t_map_setting *setting;
}  t_map;

typedef struct s_pressed_keys
{
    int w;
    int a;
    int s;
    int d;
    int la;
    int ra;
}   t_pressed_keys;

typedef struct s_assets
{
    t_img   *north_wall;
    t_img   *south_wall;
    t_img   *east_wall;
    t_img   *west_wall;
}   t_assets;

typedef struct s_game
{
    void        *mlx;
    void        *window;
    t_map       *map;
    t_player    *player;
    int win_width;
    int win_height;
    t_img   *cast_image;
    t_img   *main_image;
    t_pressed_keys *keys;
    t_assets    *assets;
}   t_game;

// Parser and Init
int init_map(t_game *game);
int read_map(t_map *map);

// Render
int    render_map(t_game *game);
void    check_horizontal(t_map *map, t_raycast *ray);
void    check_vertical(t_map *map, t_raycast *ray);
void    draw_rays(t_game *game);
void	draw_walls(t_game *game, t_raycast *ray, t_player *player, int rid, int color);

// Utils
unsigned int	get_pixel_img(t_img img, int x, int y);
int     init_game(t_game *game);
double  to_radians(double degrees);
double  to_degrees(double radians);
double  center_pos(double pos);
double  dist(float ax, float ay, float bx, float by);
int     get_player_tile(double player_pos);
int     get_tile_at(int x, int y, t_map *map);
void	put_pixel_img(t_img img, int x, int y, int color);
void	put_pixel_img_radius(t_img img, int x, int y, int color, int thickness);
void	put_img_to_img(t_img *dst, t_img *src, int x, int y);
void    draw_line_to_img(t_img *img, int beginX, int beginY, int endX, int endY, int color);
void    draw_rect_to_img(t_img *img, int beginX, int beginY, int endX, int endY, int color, int width);

// Managers
void    init_listener(t_game *cub);

// Listeners
int listen_exit(t_game *cub);
int listen_key_press(int keycode, t_game *cub);
int listen_key_release(int keycode, t_game *game);

// Cleanup
void    clean(t_game *game);
void    free_map(t_map *map);

#endif