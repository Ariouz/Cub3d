#include "cub3d.h"

void    draw_rays(t_game *game)
{
	t_raycast *ray;
	t_player *player;
	t_map   *map;
	int i;

	ray = malloc(sizeof(t_raycast));
	if (!ray)
		return;

	player = game->player;
	map = game->map;

	ray->ra = player->angle - DR * 30;
	if (ray->ra < 0) ray->ra += 2 * PI;
	if (ray->ra > 2 * PI) ray->ra -= 2 * PI;

	i= 0;
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
	
		check_horizontal(map, ray);
		check_vertical(map, ray);

		if (ray->dis_v < ray->dis_h)
		{
			ray->rx = ray->vx;
			ray->ry = ray->vy;
			ray->dist = ray->dis_v;
			draw_walls(game, ray, player, i, 0x770000);
		}
		if (ray->dis_h < ray->dis_v)
		{
			ray->rx = ray->hx;
			ray->ry = ray->hy;
			ray->dist = ray->dis_h;
			draw_walls(game, ray, player, i, 0xDD0000);
		}


		//draw_line_to_img(game->cast_image, player->x, player->y, ray->rx, ray->ry, 0x77FF0000);
		ray->ra += DR;
		if (ray->ra < 0) ray->ra += 2 * PI;
		if (ray->ra > 2 * PI) ray->ra -= 2 * PI;
		i++;
	}
}

void	draw_walls(t_game *game, t_raycast *ray, t_player *player, int rid, int color)
{
	double lineH;
	double lineO;
	double ca;

	ca = player->angle - ray->ra;
	if (ca < 0) ca += 2 * PI;
	if (ca > 2 * PI) ca -= 2 * PI;
	ray->dist *= cos(ca);
	lineH = (TILE_SIZE * game->win_width) / ray->dist;
	if (lineH > game->win_width) lineH = game->win_width;
	lineO = game->win_height / 2 - (lineH / 2);
	
	(void) lineO;
	(void) rid;
	(void) color;
	double ridM = game->win_width / PLAYER_FOV;
	(void) ridM;
	//printf("%f\n", ridM);
	draw_rect_to_img(game->cast_image, rid * ridM - ridM, lineO, rid * ridM + ridM, lineH + lineO, color, ridM);
	//draw_line_to_img(game->cast_image, rid * ridM, lineO, rid * ridM , lineH + lineO, color);
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
			ray->dof = 8;
		}

		while (ray->dof < 8)
		{
			ray->mx = (int) ray->rx / TILE_SIZE;
			ray->my = (int) ray->ry / TILE_SIZE;
			ray->mp = ray->my * map->width + ray->mx;
			if (ray->mp > 0 && ray->mp < map->width * map->height && map->tiles[ray->mp] == MAP_WALL)
			{
				ray->dof = 8;
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
			ray->dof = 8;
		}

		while (ray->dof < 8)
		{
			ray->mx = (int) ray->rx / TILE_SIZE;
			ray->my = (int) ray->ry / TILE_SIZE;
			ray->mp = ray->my * map->width + ray->mx;
			if (ray->mp > 0 && ray->mp < map->width * map->height && map->tiles[ray->mp] == MAP_WALL)
			{
				ray->dof = 8;
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