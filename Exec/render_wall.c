/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:58:26 by lvan-slu          #+#    #+#             */
/*   Updated: 2024/12/12 15:58:27 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= HEIGHT)
		return ;
	mlx_pixel_put(mlx->ptr, mlx->win, x, y, color);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

int	get_color(t_mlx *mlx, int flag)
{
	mlx->ply->ray_ngl = nor_angle(mlx->ply->ray_ngl);
	if (flag == 0)
	{
		if (mlx->ply->ray_ngl > PI / 2 && mlx->ply->ray_ngl < 3 * PI / 2)
			return (0xec8606);
		else
			return (0x00d105);
	}
	else
	{
		if (mlx->ply->ray_ngl > 0 && mlx->ply->ray_ngl < PI)
			return (0xFFC300);
		else
			return (0xC70039);
	}
}

void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int	color;

	color = get_color(mlx, mlx->ply->flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(mlx, ray, t_pix++, color);
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	mlx->ply->distance *= cos(nor_angle(mlx->ply->ray_ngl
				- mlx->ply->dir_angle));
	wall_height = (TILE_SIZE / mlx->ply->distance) * ((WIDTH / 2) / tan(mlx->ply->fov
				/ 2));
	bottom_pixel = ((HEIGHT / 2) + (wall_height / 2));
	top_pixel = ((HEIGHT / 2) - (wall_height / 2));
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	draw_wall(mlx, ray,top_pixel, bottom_pixel);
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
}
