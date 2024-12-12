/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:37:58 by lvan-slu          #+#    #+#             */
/*   Updated: 2024/12/05 13:37:59 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int i;

	i = b_pix;
	while (i < HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, 0xF00000); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, 0x000000); // ceiling
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0)
		return (0);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (y_map >= mlx->map->y || x_map >= mlx->map->x)
		return (0);
	if (mlx->map->map[y_map] && x_map <= (int)strlen(mlx->map->map[y_map]))
	{
		if (mlx->map->map[y_map][x_map] == '1')
			return (0);
	}
	return (1);
}

float	get_h_inter(t_mlx *mlx, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(mlx->ply->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = mlx->ply->player_x + (h_y - mlx->ply->player_y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - mlx->ply->player_x, 2) + pow(h_y
				- mlx->ply->player_y, 2)));
}

float	get_v_inter(t_mlx *mlx, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(mlx->ply->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = mlx->ply->player_y + (v_x - mlx->ply->player_x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x')
			&& y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - mlx->ply->player_x, 2) + pow(v_y
				- mlx->ply->player_y, 2)));
}

void	init_raycasting(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ply->ray_ngl = mlx->ply->dir_angle - (mlx->ply->fov / 2);
	while (ray < WIDTH)
	{
		mlx->ply->flag = 0;
		h_inter = get_h_inter(mlx, nor_angle(mlx->ply->ray_ngl));
		v_inter = get_v_inter(mlx, nor_angle(mlx->ply->ray_ngl));
		if (v_inter <= h_inter)
			mlx->ply->distance = v_inter;
		else
		{
			mlx->ply->distance = h_inter;
			mlx->ply->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ply->ray_ngl += (mlx->ply->fov / WIDTH);
	}
}
