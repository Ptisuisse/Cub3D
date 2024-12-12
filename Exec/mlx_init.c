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

#include "../cub3d.h"

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

/*Directions*/
int	game_loop(t_mlx *mlx);

int	keyhook(int key, t_mlx *mlx)
{
	double	new_x;
	double	new_y;
	render_minimap(mlx);
	if (key == 65307) // ECHAP
	{
		mlx_clear_window(mlx->ptr, mlx->win);
		exit(0);
	}
	if (key == 65362) // fleche haut
	{
		new_x = mlx->ply->player_x + cos(mlx->ply->dir_angle) * 0.5;
		new_y = mlx->ply->player_y + sin(mlx->ply->dir_angle) * 0.5;
		// collision
		if (mlx->map->map[(int)new_y][(int)new_x] != '1')
		{
			mlx->ply->player_x = new_x;
			mlx->ply->player_y = new_y;
		}
	}
	if (key == 65364) // fleche bas
	{
		new_x = mlx->ply->player_x - cos(mlx->ply->dir_angle) * 0.5;
		new_y = mlx->ply->player_y - sin(mlx->ply->dir_angle) * 0.5;
		// collision
		if (mlx->map->map[(int)new_y][(int)new_x] != '1')
		{
			mlx->ply->player_x = new_x;
			mlx->ply->player_y = new_y;
		}
	}
	if (key == 65361) // gauche
	{
		mlx->ply->dir_angle -= 0.1;
		if (mlx->ply->dir_angle < 0)
		{
			mlx->ply->dir_angle += 2 * PI;
		}
	}
	if (key == 65363) // droite
	{
		mlx->ply->dir_angle += 0.1;
		if (mlx->ply->dir_angle < 0)
		{
			mlx->ply->dir_angle += 2 * PI;
		}
	}
	//init_raycasting(mlx);
	draw_fov_ray(mlx);
	game_loop(mlx);
	return (0);
}

/*Initialisation de la mlx*/

int	game_loop(t_mlx *mlx)
{
	init_raycasting(mlx);
	
	//hook(mlx, 0, 0);
	return (0);
}

int	ft_mlx_init(t_mlx *mlx)
{
	mlx->ply->player_x = mlx->map->p_x; // init pos player dans struct ply
	mlx->ply->player_y = mlx->map->p_y; // init pos player dans struct ply
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Cub3D");
	//init_raycasting(mlx);
	// hook(mlx, 0, 0); // hook the player
	mlx_hook(mlx->win, 2, 1L << 0, keyhook, mlx);
	//mlx_loop_hook(mlx->ptr, &game_loop, mlx); // cast the rays
	mlx_loop(mlx->ptr);
	return (0);
}
