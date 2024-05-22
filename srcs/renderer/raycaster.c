#include "cub3d.h"

void    draw_rays(t_game *game)
{
	t_raycast *ray;
	t_player *player;
	t_map   *map;
	int i;
	int cardinal;

	ray = malloc(sizeof(t_raycast));
	if (!ray)
		return;

	player = game->player;
	map = game->map;

	ray->ra = player->angle - to_radians(30);
	if (ray->ra < 0) ray->ra += 2 * PI;
	if (ray->ra > 2 * PI) ray->ra -= 2 * PI;

	i= 0;
	cardinal = CARDINAL_NS;
	while (i < PLAYER_FOV)
	{
		ray->px = player->x;
		ray->py = player->y;

		ray->dis_h = 1000000;
		ray->hx = ray->px;
		ray->hy = ray->py;
		ray->dis_v = 1000000;
		ray->vx = ray->px;
		ray->vy = ray->py;
		ray->dist = 0;
	
		check_horizontal(map, ray);
		check_vertical(map, ray);

		if (ray->dis_v < ray->dis_h)
		{
			cardinal = CARDINAL_WE;
			ray->rx = ray->vx;
			ray->ry = ray->vy;
			ray->dist = ray->dis_v;
			draw_walls(game, ray, player, i, cardinal);
		}
		if (ray->dis_h < ray->dis_v)
		{
			cardinal = CARDINAL_NS;
			ray->rx = ray->hx;
			ray->ry = ray->hy;
			ray->dist = ray->dis_h;
			draw_walls(game, ray, player, i, cardinal);
		}

		// Afficher rayons
		//draw_line_to_img(game->cast_image, player->x, player->y, ray->rx, ray->ry, 0x77FF0000);

		ray->ra += to_radians(1);
		if (ray->ra < 0) ray->ra += 2 * PI;
		if (ray->ra > 2 * PI) ray->ra -= 2 * PI;
		i++;
	}
}


void	draw_walls(t_game *game, t_raycast *ray, t_player *player, int rid, int cardinal)
{
	double lineH;
	double lineO;
	double ca;

	ca =player->angle - ray->ra;
	if (ca < 0) ca += 2 * PI;
	if (ca > 2 * PI) ca -= 2 * PI;
	ray->dist *= cos(ca);
	lineH = (TILE_SIZE * game->win_height) / ray->dist;
	double step;
	double ty_off;
	step = 32 / lineH;
	ty_off = 0;
	if (lineH > game->win_height)
	{
		ty_off = (lineH - game->win_height) / 2;
		lineH = game->win_height;
	}
	lineO = game->win_height / 2 - (lineH / 2);
	double ridM = (double) game->win_width / PLAYER_FOV;

	int y;
	double ty;
	double tx;

	t_img *texture;
	y = 0;
	ty = (int) ty_off * step;
	if (cardinal == CARDINAL_NS)
	{
		tx = (int) (ray->rx / 2) % 32;
		texture = game->assets->north_wall;
		if (to_degrees(ray->ra) > 180)
		{
			tx = 31-tx;
			texture = game->assets->south_wall;

		}
	}
	else
	{
		tx = (int) (ray->ry / 2) % 32;
		texture = game->assets->east_wall;
		if (to_degrees(ray->ra) > 90 && to_degrees(ray->ra) < 270)
		{
			texture = game->assets->west_wall;
			tx = 31-tx;
		}
	}

	// texture painting
	while (y < lineH)
	{
		put_pixel_img_radius(*game->cast_image,  rid * ridM, y + lineO, get_pixel_img(*texture, tx,  ty), ridM);
		y++;
		ty += step;
	}

	// floor and ceilling
	y = lineO + lineH;
	while (y < game->win_height)
	{
		put_pixel_img_radius(*game->cast_image,  rid * ridM, y, game->assets->floor_color, ridM);
		put_pixel_img_radius(*game->cast_image,  rid * ridM, game->win_height - y - 16, game->assets->ceil_color, ridM);
		y++;
	}
}

void    check_horizontal(t_map *map, t_raycast *ray)
{
		ray->dof = 0;
		ray->atan = -1 / tan(ray->ra);

		if(ray->ra > PI)
		{
			ray->ry = (((int) ray->py / TILE_SIZE) * TILE_SIZE) - 0.0001;
			ray->rx = (ray->py - ray->ry) * ray->atan + ray->px;
			ray->yo = -TILE_SIZE;
			ray->xo = -ray->yo * ray->atan;
		}

		if(ray->ra < PI)
		{
			ray->ry = (((int) ray->py / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			ray->rx = (ray->py - ray->ry) * ray->atan + ray->px;
			ray->yo = TILE_SIZE;
			ray->xo = -ray->yo * ray->atan;
		}

		if (ray->ra == 0 || ray->ra == PI)
		{
			ray->rx = ray->px;
			ray->ry = ray->py;
			ray->dof = 64;
		}

		while (ray->dof < 64)
		{
			ray->mx = (int) ray->rx / TILE_SIZE;
			ray->my = (int) ray->ry / TILE_SIZE;
			ray->mp = ray->my * map->width + ray->mx;
			if (ray->mp > 0 && ray->mp < map->width * map->height && map->tiles[ray->mp] == MAP_WALL)
			{
				ray->dof = 64;
				ray->hx = ray->rx;
				ray->hy = ray->ry;
				ray->dis_h = dist(ray->px, ray->py, ray->hx, ray->hy);
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof+=1;
			}
		}
}

void    check_vertical(t_map *map, t_raycast *ray)
{
		ray->dof = 0;
		ray->atan = -tan(ray->ra);

		if(ray->ra > P2 && ray->ra < P3)
		{
			ray->rx = (((int) ray->px / TILE_SIZE) * TILE_SIZE) - 0.0001;
			ray->ry = (ray->px - ray->rx) * ray->atan + ray->py;
			ray->xo = -TILE_SIZE;
			ray->yo = -ray->xo * ray->atan;
		}

		if(ray->ra < P2 || ray->ra > P3)
		{
			ray->rx = (((int) ray->px / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
			ray->ry = (ray->px - ray->rx) * ray->atan + ray->py;
			ray->xo = TILE_SIZE;
			ray->yo = -ray->xo * ray->atan;
		}

		if (ray->ra == 0 || ray->ra == PI)
		{
			ray->rx = ray->px;
			ray->ry = ray->py;
			ray->dof = 64;
		}

		while (ray->dof < 64)
		{
			ray->mx = (int) ray->rx / TILE_SIZE;
			ray->my = (int) ray->ry / TILE_SIZE;
			ray->mp = ray->my * map->width + ray->mx;
			if (ray->mp > 0 && ray->mp < map->width * map->height && map->tiles[ray->mp] == MAP_WALL)
			{
				ray->dof = 64;
				ray->vx = ray->rx;
				ray->vy = ray->ry;
				ray->dis_v = dist(ray->px, ray->py, ray->vx, ray->vy);
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof+=1;
			}
		}
}