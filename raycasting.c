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

int unit_circle(float angle, char c)
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

int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
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


void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)	// put the pixel
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

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;

	i = b_pix;
	while (i < HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, 0xF00000); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, 0xF00000); // ceiling
}

int	get_color(t_mlx *mlx, int flag)	// get the color of the wall
{
	mlx->ply->ray_ngl = nor_angle(mlx->ply->ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ply->ray_ngl > PI / 2 && mlx->ply->ray_ngl < 3 * (PI / 2))
			return (0xF00000); // west wall
		else
			return (0xF00000); // east wall
	}
	else
	{
		if (mlx->ply->ray_ngl > 0 && mlx->ply->ray_ngl < PI)
			return (0xF00000); // south wall
		else
			return (0xF00000); // north wall
	}
}

void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = get_color(mlx, mlx->ply->flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(mlx, ray, t_pix++, color);
}


void	render_wall(t_mlx *mlx, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ply->distance *= cos(nor_angle(mlx->ply->ray_ngl - mlx->ply->dir_angle)); // fix the fisheye
	wall_h = (TILE_SIZE / mlx->ply->distance) * ((WIDTH / 2) / tan(FOV / 2)); // get the wall height
	b_pix = (HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

/*h_inter diff double et float*/
float get_h_inter(t_mlx *mlx, float angle)
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
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (mlx->map->map[(int)h_y][(int)h_x] != '1')
	{
		h_x += x_step;
		h_y += y_step;float	h_x;
			float	h_y;
			float	x_step;
			float	y_step;
			int		pixel;
		
			y_step = TILE_SIZE;
			x_step = TILE_SIZE / tan(angle);
			h_y = floor(mlx->ply->player_y / TILE_SIZE) * TILE_SIZE;
			pixel = inter_check(angle, &h_y, &y_step, 1);
			h_x = mlx->ply->player_x + (h_y - mlx->ply->player_y) / tan(angle);
			if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
				x_step *= -1;
			while (mlx->map->map[(int)h_y][(int)h_x] != '1')
			{
				h_x += x_step;
				h_y += y_step;
			}
			return (sqrt(pow(h_x - mlx->ply->player_x, 2) + pow(h_y - mlx->ply->player_y, 2)));
	}
	return (sqrt(pow(h_x - mlx->ply->player_x, 2) + pow(h_y - mlx->ply->player_y, 2)));
}

float get_v_inter(t_mlx *mlx, float angle)
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
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (mlx->map->map[(int)y_step][(int)x_step] != '1')
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - mlx->ply->player_x, 2) + pow(v_y - mlx->ply->player_y, 2)));
}

void	init_raycasting(t_mlx *mlx)
{
	double h_inter;
	double v_inter;
	int ray;

	ray = 0;
	//Angle Rayon = angle du joueur - FOV en radian
	mlx->ply->ray_ngl = mlx->ply->dir_angle - (FOV / 2); // the start angle
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
		mlx->ply->ray_ngl += (FOV / WIDTH);
	}
}