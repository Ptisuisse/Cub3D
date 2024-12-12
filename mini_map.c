/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:22:52 by lvan-slu          #+#    #+#             */
/*   Updated: 2024/12/05 12:23:05 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel_player(t_mlx *mlx, double y, double x, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	// Centre du player
	start_x = (int)(x * 10);
	start_y = (int)(y * 10);
	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, start_x + i, start_y + j, color);
			i++;
		}
		j++;
	}
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = x * 10;
	start_y = y * 10;
	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, start_y + i, start_x + j, color);
			i++;
		}
		j++;
	}
}

void	draw_fov_ray(t_mlx *mlx)
{
	double	a_ray_x;
	double	a_ray_y;
	double	angle;
	int		rays;
	double	start_angle;

	start_angle = mlx->ply->dir_angle - (PI / 4) / 2;
	angle = mlx->ply->dir_angle;
	rays = 0;
	while (rays < 100)
	{
		a_ray_x = mlx->ply->player_x + 0.5;
		a_ray_y = mlx->ply->player_y + 0.5;
		angle = start_angle + (rays * (PI / 4) / 100);
		while (mlx->map->map[(int)a_ray_y][(int)a_ray_x] != '1')
		{
			mlx_pixel_put(mlx->ptr, mlx->win, a_ray_x * 10, a_ray_y * 10,
				0xFF0000);
			a_ray_x += cos(angle) * 0.01;
			a_ray_y += sin(angle) * 0.01;
		}
		rays++;
	}
}

int	render_minimap(t_mlx *mlx)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (mlx->map->map[y])
	{
		x = 0;
		while (mlx->map->map[y][x])
		{
			ft_put_pixel_player(mlx, mlx->ply->player_y, mlx->ply->player_x,
				0xF00000);
			if (mlx->map->map[y][x] == '1')
				ft_put_pixel(mlx, y, x, 0x87CEEB);
			else if (mlx->map->map[y][x] >= '0')
				ft_put_pixel(mlx, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx->map->minimap = true;
	draw_fov_ray(mlx);
	return (1);
}
