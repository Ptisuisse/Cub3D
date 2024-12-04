/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvan-slu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:32:05 by lvan-slu          #+#    #+#             */
/*   Updated: 2024/11/26 11:32:06 by lvan-slu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Taille de la map*/
void	size_of_map(t_data_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[map->y])
	{
		map->x = 0;
		while (map->map[map->y][map->x])
		{
			if (map->map[map->y][map->x] == 'N')
			{
				map->p_x = map->x;
				map->p_y = map->y;
			}
			map->x++;
		}
		if (map->x > j)
			j = map->x;
		map->y++;
		if (map->y > i)
			i = map->y;
	}
	map->x = j;
	map->y = i;
}

void ft_put_pixel_player(t_mlx *mlx, double y, double x, int color)
{
    int i;
    int j;
    int start_x;
    int start_y;

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

void draw_fov_ray(t_mlx *mlx)
{
	double ray_x;
	double ray_y;
	double angle;
	int	rays;
    const double ANGLE_STEP = (PI/4) / 100;
    double start_angle = mlx->ply->dir_angle - (PI/4) / 2;
	angle = mlx->ply->dir_angle;
	rays = 0;
	while (rays < 100)
	{
		ray_x = mlx->ply->player_x + 0.5;
		ray_y = mlx->ply->player_y + 0.5;
		angle = start_angle + (rays * ANGLE_STEP);
		while (mlx->map->map[(int)ray_y][(int)ray_x] != '1')
		{
			mlx_pixel_put(mlx->ptr, mlx->win, ray_x * 10, ray_y * 10, 0xFF0000);
            ray_x += cos(angle) * 0.01;
            ray_y += sin(angle) * 0.01;
		}
		rays++;
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
			mlx_pixel_put(mlx->ptr, mlx->win, start_y + i, start_x
				+ j, color);
			i++;
		}
		j++;
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
			if (mlx->map->map[y][x] == '1')
				ft_put_pixel(mlx, y, x, 0x87CEEB);
			else
				ft_put_pixel(mlx, y, x, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx->map->minimap = true;
	draw_fov_ray(mlx);
	ft_put_pixel_player(mlx, mlx->ply->player_y, mlx->ply->player_x, 0xF00000);
	return (1);
}


/*Directions*/

int	keyhook(int key, t_mlx *mlx)
{
	double new_x;
    double new_y;

	if (key == 65307) // ECHAP
	{
		mlx_clear_window(mlx->ptr, mlx->win);
		exit(0);
	}
    if (key == 65362) // fleche haut
    {
        new_x = mlx->ply->player_x + cos(mlx->ply->dir_angle) * 0.1;
        new_y = mlx->ply->player_y + sin(mlx->ply->dir_angle) * 0.1;
        
        // collision
        if (mlx->map->map[(int)new_y][(int)new_x] != '1')
        {
            mlx->ply->player_x = new_x;
            mlx->ply->player_y = new_y;
        }
    }
	if (key == 65364) //fleche bas
	{
		new_x = mlx->ply->player_x - cos(mlx->ply->dir_angle) * 0.1;
		new_y = mlx->ply->player_y - sin(mlx->ply->dir_angle) * 0.1;
		
		// collision

		if (mlx->map->map[(int)new_y][(int)new_x] != '1')
		{
			mlx->ply->player_x = new_x;
			mlx->ply->player_y = new_y;
		}
	}
	if (key == 65361) //gauche
	{
		mlx->ply->dir_angle -= 0.1;
		if (mlx->ply->dir_angle < 0)
		{
			mlx->ply->dir_angle += 2 * PI;
		}
	}
	if (key == 65363) //droite
	{
		mlx->ply->dir_angle += 0.1;
		if (mlx->ply->dir_angle < 0)
		{
			mlx->ply->dir_angle += 2 * PI;
		}
	}
	render_minimap(mlx);
	draw_fov_ray(mlx); 
	return (0);
}

/*Initialisation de la mlx*/

int	ft_mlx_init(t_mlx *mlx)
{
	mlx->ply->player_x = mlx->map->p_x + 0.5; // init pos player dans struct ply
	mlx->ply->player_y = mlx->map->p_y + 0.5; // init pos player dans struct ply
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, 1080, 720, "Cub3D");
	mlx_hook(mlx->win, 2, 1L << 0, keyhook, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
