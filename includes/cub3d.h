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
# include <stdint.h>
# include <stddef.h>

# define PI 3.1415926535
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533

# define CARDINAL_NS 1
# define CARDINAL_WE 0

# define FOG_COLOR 0x111111
# define PLAYER_SPEED 12
# define PLAYER_ROTATION_SPEED 0.2
# define TL_S 64
# define MN_TSIZE 12
# define PLAYER_FOV 60

# define MNMP_SLEN 100

# define DESTROY_HOOK 17
# define KEY_PRESSED_HOOK 2
# define KEY_RELEASE_HOOK 3
# define MOUSE_MOVE_HOOK 6

# define KEY_ESCAPE 65307
# define KEY_SPACE 32
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_LEFT 65361

# define MAP_WALL 1
# define MAP_AIR 0

# define PARAMETER_NUMBER_ERROR "This program must take one .cub file\n"
# define WRONG_FILE_EXTENSION "The map must be a '.cub' file\n"
# define WRONG_MAP_ARGUMENT "There is a wrong parameter in the map\n"
# define MISSING_ASSETS "They are some missing assets\n"
# define MULTIPLE_FILE_TO_SAME_TEXTURE "Can't assign multiple file to the same texture\n"
# define MULTIPLE_COLOR_TO_SAME_TEXTURE "Can't assign multiple color to the same texture\n"
# define WRONG_COLOR "The color given in parameter is not valid\n"
# define WRONG_RGB_VALUE "The RGB value must be between 0 and 255\n"
# define MALLOC_ERROR "malloc allocation failed\n"
# define MLX_INIT_ERROR "mlx initialisation failed\n"
# define MLX_WINDOWS_INIT_ERROR "mlx windows initialisation failed\n"
# define MLX_NEW_IMG_ERROR "mlx new image function failed\n"
# define MLX_FILE_TO_IMAGE_ERROR "mlx file to image failed\n"
# define MAP_DESCRIPTION_ERROR "The map description have an incorrect element\n"
# define MAP_DESCRIPTION_PLAYER_ERROR "The map description must have only one player spawn\n"
# define MAP_DESCRIPTION_WALL_ERROR "The map description must close by wall\n"

typedef struct s_save_line
{
    int rows;
    int cols;
    int index;
}   t_save_line;

typedef struct s_vector
{
    double  dx;
    double  dy;
    int     ix;
    int     iy;
}   t_vector;


typedef struct s_color
{
    int r;
    int g;
    int b;
}  t_color;

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
    int    mouseX;
}   t_player;

typedef struct s_map
{
    int *tiles;
    int height;
    int width;
    int player_x;
    int player_y;
    int size;
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
    int     floor_color;
    int     ceil_color;
}   t_assets;

typedef struct s_game
{
    void        *mlx;
    void        *window;
    t_map       *map;
    t_player    *player;
    int win_width;
    int win_height;
    int mouse_lock;
    int spawn_angle;
    t_img   *cast_image;
    t_img   *main_image;
    t_pressed_keys *keys;
    t_assets    *assets;
}   t_game;

// Parser and Init
int     init_map(t_game *game, char **argv);
int     read_map_temp(t_game *game, char **argv);
int     get_asset(t_game *game, char **temp_map);
int	    get_east_asset(t_game *game, t_assets *assets, char *line);
int	    get_north_asset(t_game *game, t_assets *assets, char *line);
int	    get_west_asset(t_game *game, t_assets *assets, char *line);
int	    get_south_asset(t_game *game, t_assets *assets, char *line);
int	    get_floor_color(t_game *game, t_assets *assets, char *line);
int	    get_ceiling_color(t_game *game, t_assets *assets, char *line);
int	    get_color(t_game *game, int *color, char *line);
char	**get_map_description(char **map);
int	    check_map(t_game *game, char **map);
int	    check_element(t_game *game, char **map);
int	    check_wall(char **map);
int	    get_int_map(t_game *game, char **map);

// Render
int     render_map(t_game *game);
void    draw_minimap(t_game *game, t_map *map, t_player *player);
void    print_coords(t_game *game);
void    show_tooltip(t_game *game);
void    check_horizontal(t_map *map, t_raycast *ray);
void    check_vertical(t_map *map, t_raycast *ray);
void    draw_rays(t_game *game);
void	draw_walls(t_game *game, t_raycast *ray, t_player *player, t_vector infos);
void	draw_floor_ceil(t_vector vars, t_vector infos, t_vector line_vec,
	t_game *game);
void	prevent_line_oversize(t_vector *line_vec, t_vector *tex_vec,
	t_game *game);
t_img	*get_texture(t_raycast *ray, t_vector infos, t_vector *tcoord,
	t_game *game);

// Utils
int	get_pixel_color_fog(t_raycast *ray, int color);
unsigned int	get_pixel_img(t_img img, int x, int y);
t_color	get_color_struct(int rgb);
int     init_game(t_game *game, int argc, char **argv);
int     mix_colors(t_color *c1, t_color *c2, double c2_factor);
double  to_radians(double degrees);
double  to_degrees(double radians);
double  center_pos(double pos);
double  dist(float ax, float ay, float bx, float by);
int     error_msg(t_game *game, char *err_msg);
int     error_open(t_game *game, char *file);
int     get_player_tile(double player_pos);
int     get_tile_at(int x, int y, t_map *map);
void	put_pixel_img(t_img img, int x, int y, int color);
void	put_pixel_img_radius(t_img img, t_vector vec, int color, int thickness);
void	put_img_to_img(t_img *dst, t_img *src, int x, int y);
void	draw_line_to_img(t_img *img, t_vector v1, t_vector v2, int color);
void	draw_rect_to_img(t_img *img, t_vector v1, t_vector v2, int color);
double	fix_ang(double a);

t_vector    vector(double x, double y);
// Managers
void    init_listener(t_game *cub);
void	move(t_game *game, t_player *pl, t_pressed_keys *keys);
void	move_side(t_player *player, t_pressed_keys *keys, t_map *map);
void	handle_rotation(t_player *player, t_pressed_keys *keys);

// Listeners
int listen_exit(t_game *cub);
int listen_key_press(int keycode, t_game *cub);
int listen_key_release(int keycode, t_game *game);
int listen_mousemove(int x, int y, t_game *game);

// Cleanup
void    clean(t_game *game);
void    free_assets(t_game *game);
void    free_map(t_map *map);
void    free_temp_map(char **map);

#endif